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

TaskList* create_list(size_t initial_capacity)
{
    TaskList *today = malloc (sizeof (TaskList));
    if (today == NULL) return NULL;

    today -> size = 0;
    today -> allocated = initial_capacity;
    today -> items = maloc (initial_capacity * sizeof (Task*));

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
    newtask -> target_duration = 0;
    newtask -> scheduled_time = 0;
    newtask->is_permanent = permanent;

    return newtask;
}

void free_list(TaskList* list)
{
    for (int i = 0; i < list -> size; ++i)
    {
        free (list -> items [i]);
    }

    if (list -> items != NULL)
    free (list -> items);

    free (list);
}