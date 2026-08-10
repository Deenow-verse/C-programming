#include <stdio.h> 
#include <stdbool.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#define MAX 120

typedef struct 
{
    char name [MAX];
    int target_duration;
    time_t scheduled_time;
    bool completion_status;
    uint8_t recurrence_mask;
} Task;

typedef struct
{
    time_t now;
    int total_task;
    int completed_tasks;
    int total_minutes_logged;
} DailySummary;

typedef struct
{
    size_t size;
    size_t allocated;
    Task **items;
} TaskList;

TaskList* create_list(size_t initial_capacity);
Task* create_task(const char* name, int duration, time_t scheduled, uint8_t recurrence_mask);
void free_list(TaskList* list);
bool append_task(TaskList *list, Task *new_task);
time_t get_day_start_time(void);
bool save_tasks(TaskList *list, const char *filename);
TaskList* load_tasks(const char *filename);
void render_dashboard(TaskList *list);
void start_pomodoro(Task *task);
TaskList* rollover_day(TaskList *old_list);
void render_calendar(void);

int main(void)
{
    const char *db_file = ".underworld.dat";
    
    TaskList *today_list = load_tasks(db_file);

    if (today_list != NULL && today_list->size > 0)
    {
        if (today_list->items[0]->scheduled_time < get_day_start_time())
        {
            today_list = rollover_day(today_list);
            save_tasks(today_list, db_file);
        }
    }
    
    while (1)
    {
        render_dashboard(today_list);

        printf ("[1] Refresh Dashboard\n");
        printf ("[2] Add a New Task\n");
        printf ("[3] Mark Task Complete\n");
        printf ("[4] Exit and Save\n");
        printf ("[5] Start Focus Block\n");
        printf ("\n\nPLAN YOUR FUTURE\n");

        size_t option;
        scanf ("%zu", &option);

        if (option == 2)
        {
            int i = 0;

            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            char temp_name[MAX];
            char buffer[MAX];

            printf("Enter the name of the task:\n");
            fgets(temp_name, MAX, stdin);
            
            temp_name[strcspn(temp_name, "\n")] = 0;
            
            printf("Enter the target duration (mins):\n");
            fgets(buffer, MAX, stdin);
            int temp_duration = atoi(buffer);

            printf("Recurrence:\n[0] Once\n[1] Daily\n[2] Weekly (On this exact day)\nChoice: ");
            fgets(buffer, MAX, stdin);
            int rec_choice = atoi(buffer);

            uint8_t mask = 0;
            if (rec_choice == 1)
            {
                mask = 127;
            }

            else if (rec_choice == 2)
            { 
                time_t now = get_day_start_time();
                struct tm *time_info = localtime(&now);
                mask = (1 << time_info->tm_wday); 
            }

            Task *t = create_task(temp_name, temp_duration, get_day_start_time(), mask);
            append_task(today_list, t);

            printf("Added new task: %s\n", t->name);

            if (save_tasks(today_list, db_file))
            {
                printf("Engine state saved successfully.\n");
            }
            else
            {
                printf("ERROR: Failed to save engine state!\n");
            }

            ++i;
        }

        else if (option == 3)
        {
            if (today_list == NULL)
            printf ("No saved task\n");

           /*else
            {
                printf("--- CURRENT TASKS ---\n");
                for (size_t i = 0; i < today_list->size; i++)
                {
                    printf("[%zu] [%c] %s (%d mins)\n", i, today_list->items[i]->completion_status ? 'X' : ' ', today_list->items[i]->name,today_list->items[i]->target_duration);
                }
                printf("---------------------\n");
            }*/
            
            printf ("ENTER THE TASK NUMBER YOU HAVE FOR THE TASK YOU HAVE COMPLETED\n");
            scanf ("%zu", &option);

            if (option >= 0 && option < today_list->size)
            {
                today_list->items[option]->completion_status = true; 
                printf("Task %zu marked complete!\n", option);
            }
            else
            {
                printf("Invalid task number.\n");
            } 

        }

        else if (option == 4)
        {
            save_tasks (today_list, db_file);
            free_list(today_list);
            break;
        }

        else if (option == 5)
        {
            printf ("which task do you want to focus on? ");
            scanf ("%zu", &option);

            start_pomodoro (today_list -> items [option]);
        }

        else
        printf ("You have entered the wrong option. Please select from the above displayed options");

    }    

    

    return 0;
}

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

void render_dashboard(TaskList *list)
{
    printf("\033[2J\033[H");

    printf("\033[44m=== THE UNDERWORLD TRACKER =============================\033[0m\n\n");

    render_calendar();
    printf ("\n");

    if (list == NULL || list->size == 0) {
        printf("No tasks found for today. Plan your future.\n\n");
        return;
    }

    printf("--- CURRENT TASKS ---\n");
    for (size_t i = 0; i < list->size; i++)
    {
        char status_char = list->items[i]->completion_status ? 'X' : ' ';
        const char *color = list->items[i]->completion_status ? "\033[32m" : "";
        const char *reset = "\033[0m";

        printf("[%zu] [%s%c%s] %-30s (%3d mins)\n", 
            i, 
            color, status_char, reset,       
            list->items[i]->name,            
            list->items[i]->target_duration);
    } 
    printf("--------------------------------------------------------\n\n");
}

void start_pomodoro(Task *task)
{
    int total_seconds = task->target_duration * 60;

    while(total_seconds > 0)
    {
        int minutes = total_seconds / 60;
        int seconds = total_seconds % 60;

        printf("\rTime remaining: %02d:%02d", minutes, seconds);
        fflush(stdout);

        sleep(1);
        --total_seconds;
    }

    printf("\nFocus block complete!\n"); sleep(2);
    task->completion_status = true;
    
    return;
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
        if (old_list->items[i]->recurrence_mask & (1 << new_wday))
        {
            Task *cloned_task = create_task(
                old_list->items[i]->name, 
                old_list->items[i]->target_duration, 
                new_day_time, 
                old_list->items[i]->recurrence_mask
            );
            append_task(new_list, cloned_task);
        }
    }

    free_list(old_list);
    return new_list;
}

void render_calendar(void)
{
    int i = 0;
    DailySummary Buffer_history [MAX];
    FILE *file = fopen(".underworld_history.dat", "rb");
    if (file == NULL)
    {
        printf ("No history yet.\n");
        return;
    }

    while (fread(&Buffer_history[i], sizeof (Buffer_history[i]), 1, file ) == 1)
    {
        int percent = 0;

        if (Buffer_history[i].total_task > 0)
        percent = (Buffer_history [i].completed_tasks * 100) / Buffer_history [i].total_task;

        else
        break;

        if (percent == 0)
        {
            printf ("\033[0m [ ] \033[0m");
        }

        else if (percent >= 1 && percent <=49)
        {
            printf ("\033[48;5;117m [ ] \033[0m");
        }

        else if (percent >= 50 && percent <= 99)
        {
            printf ("\033[48;5;33m [ ] \033[0m");
        }

        else
        printf ("\033[48;5;21m\033[37m [X] \033[0m");

        ++i;
        
    }

    fclose (file);
}