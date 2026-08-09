#include <stdbool.h>
#include <time.h>
#include <stddef.h>

#define MAX 120

typedef struct 
{
    char name [MAX];
    int target_duration;
    time_t scheduled_time;
    bool completion_status;
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

