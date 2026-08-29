#include "tracker.h"

TaskList* create_list(size_t initial_capacity)
{
    TaskList *today = malloc (sizeof (TaskList));
    if (today == NULL)
    return NULL;

    today -> size = 0;
    today -> allocated = initial_capacity;
    today -> items = malloc (initial_capacity * sizeof (Task*));

    if (today->items == NULL)
    {
        free(today); 
        return NULL;
    }    

    return today;
}

Task* create_task(const char* name, int duration, time_t scheduled, uint8_t recurrence_mask)
{
    Task *newtask = malloc (sizeof (Task));

    strncpy(newtask->name, name, MAX - 1);
    newtask->name[MAX - 1] = '\0';

    newtask -> completion_status = false;
    newtask -> target_duration = duration;
    newtask -> scheduled_time = scheduled;
    newtask-> recurrence_mask = recurrence_mask;

    return newtask;
}

void free_list(TaskList* list)
{
    if (list == NULL)
    return;

    for (int i = 0; i < list -> size; ++i)
    {
        free (list -> items [i]);
    }

    if (list -> items != NULL)
    free (list -> items);

    free (list);
}

bool append_task(TaskList *list, Task *new_task)
{
    size_t newsize;
    newsize = list -> size + 1;

    if (list -> size == list -> allocated)
    {
        size_t new_allocated = (newsize >> 3) + (newsize < 9 ? 3 : 6) + + newsize;
        Task **temp = realloc (list -> items, new_allocated * sizeof (Task *));

        if (temp == NULL)
        {
            fprintf(stderr , "Memory reallocation failed\n");
            exit(1);
        }

        list -> items = temp;
        list -> allocated = new_allocated;

    }

    list -> items [list -> size] = new_task;
    list -> size = newsize; 

    return true;

}

time_t get_day_start_time(void)
{
    time_t raw_now = time(NULL);
    struct tm *time_info = localtime(&raw_now);

    if (time_info->tm_hour < 16)
    {
        time_info->tm_mday -= 1; 
    }

    time_info->tm_hour = 16;
    time_info->tm_min = 0;
    time_info->tm_sec = 0;

    return mktime(time_info);
}

bool save_tasks(TaskList *list, const char *filename)
{
    if (list == NULL || filename == NULL)
    return false;

    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        return false;
    }

    if (fwrite(&list->size, sizeof(size_t), 1, file) != 1)
    {
        fclose(file);
        return false;
    }

    for (size_t i = 0; i < list->size; i++)
    {
        if (fwrite(list->items[i], sizeof(Task), 1, file) != 1)
        {
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;

}

TaskList* load_tasks(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        return NULL;
    }
    
    size_t task_count = 0;
    if (fread(&task_count, sizeof(size_t), 1, file) != 1)
    {
        fclose(file);
        return NULL;
    }

    TaskList *list = create_list(task_count);
    if (list == NULL)
    {
        fclose(file);
        return NULL;
    }

    for (size_t i = 0; i < task_count; i++)
    {
        Task *temp_task = malloc(sizeof(Task));

        if (temp_task == NULL)
        break;

        if (fread(temp_task, sizeof(Task), 1, file) != 1)
        {
            free(temp_task);
            break; 
        }

        append_task(list, temp_task);
    }

    fclose(file);
    return list;    

}

TaskList* rollover_day(TaskList *old_list)
{
    DailySummary summary = {0};

    if (old_list->size > 0)
    {
        summary.now = old_list->items[0]->scheduled_time;
        summary.total_task = old_list->size;

        for (size_t i = 0; i < old_list->size; i++)
        {
            if (old_list->items[i]->completion_status == true)
            {
                summary.completed_tasks++;
                summary.total_minutes_logged += old_list->items[i]->target_duration;
            }
        }

        const char *hist_file = ".underworld_history.dat";
        FILE *file = fopen(hist_file, "ab");
        if (file != NULL)
        {
            fwrite(&summary, sizeof(DailySummary), 1, file);
            fclose(file);
        }
    }

    time_t new_day_time = get_day_start_time();
    struct tm *new_day_info = localtime(&new_day_time);
    int new_wday = new_day_info->tm_wday;

    TaskList *new_list = create_list(10);

    for (size_t i = 0; i < old_list->size; i++)
    {
        if (old_list->items[i]->recurrence_mask > 0)
        {
            Task *cloned_task = create_task(old_list->items[i]->name, old_list->items[i]->target_duration, new_day_time, old_list->items[i]->recurrence_mask);
            append_task(new_list, cloned_task);
        }
    }

    free_list(old_list);
    return new_list;
}

int get_completed_tasks_count(const char *filename, time_t target_day)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        return 0; 
    }

    int count = 0;
    Task temp_task;

    while (fread(&temp_task, sizeof(Task), 1, file) == 1)
    {
        if (temp_task.completion_status == true && temp_task.scheduled_time == target_day)
        {
            count++;
        }
    }

    fclose(file);
    return count;
}

void delete_task(TaskList *list, int target_index)
{
    if (list == NULL || target_index < 0 || target_index >= list -> size)
    return;

    free(list->items[target_index]);

    for (int i = target_index; i < list->size - 1; ++i)
    {
        list->items[i] = list->items[i + 1];
    }

    list->size--;
}

void update_view_cache(TaskList *master, ViewCache *cache, int current_wday)
{
    if (master == NULL || cache == NULL) return;
    
    cache->count = 0;
    
    for (int i = 0; i < master->size; ++i)
    {
        uint8_t mask = master->items[i]->recurrence_mask;

        if (mask == 0 || (mask & (1 << current_wday)))
        {
            cache->indices[cache->count] = i;
            cache->count++;
        }
    }
}

time_t calculate_scheduled_time(time_t logical_day_start, const char *time_str)
{
    int hours = 0, mins = 0;

    if (sscanf(time_str, "%d:%d", &hours, &mins) != 2)
    {
        return logical_day_start; 
    }

    struct tm *time_info = localtime(&logical_day_start);
    
    time_info->tm_hour = hours;
    time_info->tm_min = mins;
    time_info->tm_sec = 0;

    if (hours < 16)
    {
        time_info->tm_mday += 1;
    }

    return mktime(time_info);
}