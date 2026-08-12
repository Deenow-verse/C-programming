#ifndef TRACKER_H
#define TRACKER_H

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
TaskList* rollover_day(TaskList *old_list);

#endif