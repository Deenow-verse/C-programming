#include <stdio.h> 
#include <stdbool.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAX 120

typedef struct 
{
    char name [MAX];
    int target_duration;
    time_t scheduled_time;
    bool completion_status;
    bool is_permanent;
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
Task* create_task(const char* name, int duration, time_t scheduled, bool permanent);
void free_list(TaskList* list);
bool append_task(TaskList *list, Task *new_task);
time_t get_day_start_time(void);
bool save_tasks(TaskList *list, const char *filename);
TaskList* load_tasks(const char *filename);

int main(void)
{
    const char *db_file = ".underworld.dat";
    
    TaskList *today_list = load_tasks(db_file);

    while (1)
    {
        printf ("UNDERWORLD TRACKER\n\n");

        printf ("[1] View Today's Tasks\n");
        printf ("[2] Add a New Task\n");
        printf ("[3] Mark Task Complete\n");
        printf ("[4] Exit and Save\n");
        printf ("PLAN YOUR FUTURE\n");

        int option;
        scanf ("%d", &option);

        if (option == 1)
        {
            if (today_list == NULL)
            {
                printf("No previous tasks found. Starting fresh.\n");
                today_list = create_list(10);
            }

           else
           {
                printf("Successfully loaded %zu tasks from disk.\n", today_list->size);
           }

            printf("--- CURRENT TASKS ---\n");
            for (size_t i = 0; i < today_list->size; i++)
            {
                printf("[%zu] [%c] %s (%d mins)\n", i, today_list->items[i]->completion_status ? 'X' : ' ', today_list->items[i]->name, today_list->items[i]->target_duration);
            }
            printf("---------------------\n");
        }

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

            printf("Is it permanent? (1 for Yes, 0 for No):\n");
            fgets(buffer, MAX, stdin);
            bool temp_perm = atoi(buffer) == 1;

            Task *t = create_task(temp_name, temp_duration, get_day_start_time(), temp_perm);
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

        if (option == 3)
        {
            size_t number = 0;

            if (today_list == NULL)
            printf ("No saved task\n");

            else
            {
                printf("--- CURRENT TASKS ---\n");
                for (size_t i = 0; i < today_list->size; i++)
                {
                    printf("[%zu] [%c] %s (%d mins)\n", i, today_list->items[i]->completion_status ? 'X' : ' ', today_list->items[i]->name,today_list->items[i]->target_duration);
                }
                printf("---------------------\n");
            }
            
            printf ("ENTER THE TASK NUMBER YOU HAVE FOR THE TASK YOU HAVE COMPLETED\n");
            scanf ("%zu", &number);

            if (number >= 0 && number < today_list->size)
            {
                today_list->items[number]->completion_status = true; 
                printf("Task %zu marked complete!\n", number);
            }
            else
            {
                printf("Invalid task number.\n");
            } 

        }

        if (option == 4)
        {
            save_tasks (today_list, db_file);
            free_list(today_list);
            break;
        }

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

Task* create_task(const char* name, int duration, time_t scheduled, bool permanent)
{
    Task *newtask = malloc (sizeof (Task));

    strncpy(newtask->name, name, MAX - 1);
    newtask->name[MAX - 1] = '\0';

    newtask -> completion_status = false;
    newtask -> target_duration = duration;
    newtask -> scheduled_time = scheduled;
    newtask->is_permanent = permanent;

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