#include "engine.h"
#include "my_math.h"
#include "tracker.h"

int main (void)
{
    int screen_width = 1920;
    int screen_height = 1080;

    int target_time_per_frame = 16666;

    Rectangle clock_btn;
    Rectangle list;
    Rectangle name_box = {240, 40, 300, 40};
    Rectangle time_box = {560, 40, 100, 40};
    Rectangle dur_box  = {680, 40, 100, 40};
    Rectangle rec_box  = {800, 40, 100, 40};

    list.width =screen_width - 210;
    list.length = screen_height;
    list.x = 210;
    list.y = 0;

    clock_btn.width = 90;
    clock_btn.length = 90;
    clock_btn.x = screen_width - clock_btn.width - 50;
    clock_btn.y =  50;

    bool is_timer_running = false;

    int focused_box = 0;
    char name_buffer[120] = {0};
    char time_buffer[16] = {0};
    char dur_buffer[16] = {0};
    char rec_buffer[16] = {0};
    int name_len = 0, dur_len = 0, rec_len = 0;
    
    Engine_InitWindow (screen_width, screen_height, "Underworld Tracker");

    time_t timer_segment_start = 0;
    int task_duration = 0;
    int time_len = 0;
    int total_seconds = task_duration * 60;
    int remaining_seconds = total_seconds;
    int active_task = -1;
    bool is_edit_mode = false;
    
    RGBA_Colour bg = {255, 255, 255, 255};
    RGBA_Colour center = {198, 228, 255, 255};
    RGBA_Colour clock = {246, 114, 56, 255  };
    RGBA_Colour clock_active = {46, 204, 113, 255};
    RGBA_Colour grid = {236, 236, 242, 255};
    RGBA_Colour square ={56, 139, 253, 255};
    RGBA_Colour sidebar = {219, 109, 40, 255};
    RGBA_Colour text = {0, 0, 0, 255};
    RGBA_Colour low_activity = {255, 212, 166, 255};
    RGBA_Colour medium_activity = {254, 173, 98, 255};
    RGBA_Colour optimum_activity = {247, 127, 0, 255};
    RGBA_Colour high_activity = {214, 73, 0, 255};

    const char *db_file = ".underworld.dat";
    TaskList *today_list = load_tasks(db_file);

    if (today_list == NULL)
    {
        today_list = create_list(10);
    }

    if (today_list != NULL && today_list->size > 0)
    {
        if (today_list->items[0]->scheduled_time < get_day_start_time())
        {
            today_list = rollover_day(today_list);
            save_tasks(today_list, db_file);
        }
    }

    time_t today_midnight = get_day_start_time();
    struct tm *time_info = localtime(&today_midnight);
    int current_wday = time_info->tm_wday;

    ViewCache view = {0};
    update_view_cache(today_list, &view, current_wday);



    int heatmap_scores[364] = {0};

    for (int i = 0; i < 364; i++)
    {
        time_t target = today_midnight - ((363 - i) * 86400);
        heatmap_scores[i] = get_completed_tasks_count(db_file, target);
    }

    while (!Engine_WindowShouldClose())
    {
        
        Engine_BeginDrawing ();

        Engine_ClearBackground (bg);

        Engine_DrawRectangle   (0, 0, 210, screen_height, sidebar);

        Engine_DrawRectangle(list.x, list.y, list.width, list.length , center);

        Engine_DrawRectangle(name_box.x, name_box.y, name_box.width, name_box.length, focused_box == 1? clock_active : center);
        Engine_DrawText(name_box.x + 10, name_box.y + 25, name_buffer, text);

        if (name_len == 0 && focused_box != 1)
        {
            Engine_DrawText(name_box.x + 10, name_box.y + 25, "Click here to add the name of the new task...", text);
        }

        Engine_DrawRectangle(time_box.x, time_box.y, time_box.width, time_box.length, focused_box == 4? clock_active : center);
        Engine_DrawText(time_box.x + 10, time_box.y + 25, time_buffer, text);

        if (time_len == 0 && focused_box != 4) {
            Engine_DrawText(time_box.x + 10, time_box.y + 25, "HH:MM", text);
        }

        Engine_DrawRectangle(dur_box.x, dur_box.y, dur_box.width, dur_box.length, focused_box == 2? clock_active : center);
        Engine_DrawText(dur_box.x + 10, dur_box.y + 25, dur_buffer, text);

        if (dur_len == 0 && focused_box != 2)
        {
            Engine_DrawText(dur_box.x + 10, dur_box.y + 25, "Mins", text);
        }

        Engine_DrawRectangle (rec_box.x, rec_box.y, rec_box.width, rec_box.length,focused_box == 3? clock_active : center);
        Engine_DrawText(rec_box.x + 10, rec_box.y + 25, rec_buffer, text);

        if (dur_len == 0 && focused_box != 2)
        {
            Engine_DrawText(rec_box.x + 10, rec_box.y + 25, "D/W/O", text);
        }       

        int box_size = 12;
        int padding = 4;
        int total_cols = 52;
        int total_rows = 7;

        int grid_width = total_cols * (box_size + padding);
        int grid_height = total_rows * (box_size + padding);

        int start_x = 210 + ((screen_width - 210) / 2) - (grid_width / 2);
        int start_y = screen_height - grid_height - 60;

        bool render_tooltip = false;
        char tooltip_text[64] = {0};
        Vector2D tooltip_pos = {0};
        Vector2D mouse_pos = { (float)Engine_GetMouseX(), (float)Engine_GetMouseY() };

        for (int col = 0; col < total_cols; col++)
        {
            for (int row = 0; row < total_rows; row++)
            {
                int x = start_x + col * (box_size + padding);
                int y = start_y + row * (box_size + padding);
                
                int day_index = (col * total_rows) + row;
                int score = heatmap_scores[day_index];

                RGBA_Colour cell_color = grid;
                if (score > 0 && score <= 5) cell_color = low_activity;
                if (score > 5 && score <= 8) cell_color = medium_activity;
                if (score > 8 && score <= 15) cell_color = medium_activity;
                if (score > 15) cell_color = high_activity;
                
                Engine_DrawRectangle(x, y, box_size, box_size, cell_color);

                if (mouse_pos.x >= x && mouse_pos.x <= (x + box_size) && mouse_pos.y >= y && mouse_pos.y <= (y + box_size))
                {
                    render_tooltip = true;
                    tooltip_pos = mouse_pos;

                    time_t hover_target = today_midnight - ((363 - day_index) * 86400);
                    struct tm *hover_info = localtime(&hover_target);
                    char date_str[32];

                    strftime(date_str, sizeof(date_str), "%b %d, %Y", hover_info);

                    if (score == 1)
                        snprintf(tooltip_text, sizeof(tooltip_text), "1 task on %s", date_str);
                    else
                        snprintf(tooltip_text, sizeof(tooltip_text), "%d tasks on %s", score, date_str);
                }
            }
        }

        if (render_tooltip)
        {
           int tip_width = 180;
            int tip_height = 26;
            int tip_x = tooltip_pos.x - (tip_width / 2);
            int tip_y = tooltip_pos.y - tip_height - 8;

            Engine_DrawRectangle(tip_x, tip_y, tip_width, tip_height, text);
            Engine_DrawText(tip_x + 8, tip_y + 18, tooltip_text, bg);
        }

        for (int v = 0; v < view.count; ++v)
        {
            int actual_index = view.indices[v];
            int text_y = 100 + (v * 30); 

            char duration_text[32];
            snprintf(duration_text, sizeof(duration_text), "%d mins", today_list->items[actual_index]->target_duration);  

            char sched_time_text[16];
            struct tm *sched_info = localtime(&today_list->items[actual_index]->scheduled_time);
            strftime(sched_time_text, sizeof(sched_time_text), "%H:%M", sched_info);

            RGBA_Colour current_color = text;

            if (today_list->items[actual_index]->completion_status == true)
            current_color = clock_active;
            else if(actual_index == active_task)
            current_color = clock;

            Engine_DrawText (name_box.x, text_y, today_list->items[actual_index]->name, current_color);
            Engine_DrawText (time_box.x, text_y, sched_time_text, current_color); 
            Engine_DrawText (dur_box.x,  text_y, duration_text, current_color);
        }       
        
        int current_display_seconds = remaining_seconds;

        if (is_timer_running)
        {
            time_t now = time(NULL);
            int elapsed = difftime(now, timer_segment_start);
            current_display_seconds = remaining_seconds - elapsed;

            if (current_display_seconds <= 0)
            {
                current_display_seconds = 0;
                is_timer_running = false;
                remaining_seconds = 0; 
                
                if (active_task != -1)
                {
                    today_list->items[active_task]->completion_status = true;
                    save_tasks(today_list, db_file);
                    update_view_cache(today_list, &view, current_wday);
                    
                    heatmap_scores[363] = get_completed_tasks_count(db_file, today_midnight);
                }
            }
        }

        if (is_timer_running)
        {
            Engine_DrawRectangle   (clock_btn.x, clock_btn.y , clock_btn.width, clock_btn.length, clock_active);
            int mins = current_display_seconds / 60;
            int secs = current_display_seconds % 60;
            char timer_text[16];
            snprintf(timer_text, sizeof(timer_text), "%02d:%02d", mins, secs);
            Engine_DrawText(clock_btn.x + 23, clock_btn.y + 45, timer_text, text);
        }
           
        else
        {
           Engine_DrawRectangle(clock_btn.x, clock_btn.y, clock_btn.width, clock_btn.length, clock);
           if (remaining_seconds > 0)
           {
                int mins = remaining_seconds / 60;
                int secs = remaining_seconds % 60;
                char timer_text[16];
                snprintf(timer_text, sizeof(timer_text), "%02d:%02d", mins, secs);
                Engine_DrawText(clock_btn.x + 23, clock_btn.y + 45, timer_text, text);
           }
        }

        if (Engine_IsMouseButtonPressed())
        {
            Vector2D mouse_pos = { (float)Engine_GetMouseX(), (float)Engine_GetMouseY() };

            if (CheckCollisionPointRec(mouse_pos, clock_btn))
            {
                if (remaining_seconds > 0 || total_seconds > 0)
                {if (is_timer_running)
                    {
                        time_t now = time(NULL);
                        int elapsed = (int)difftime(now, timer_segment_start);
                        remaining_seconds -= elapsed;
                        if (remaining_seconds < 0) remaining_seconds = 0;
                        is_timer_running = false;
                    }
                    else
                    {
                        if (remaining_seconds <= 0) remaining_seconds = total_seconds;
                        timer_segment_start = time(NULL);
                        is_timer_running = true;
                    }
                }
                
            }

            else if (CheckCollisionPointRec(mouse_pos, name_box))
            {
                focused_box = 1;
            }

            else if (CheckCollisionPointRec(mouse_pos, time_box))
            {
                focused_box = 4;
            }
            
            else if (CheckCollisionPointRec(mouse_pos, dur_box))
            {
                focused_box = 2;
            }

            else if (CheckCollisionPointRec(mouse_pos, rec_box))
            {
                focused_box = 3;
            }
            
            else if (CheckCollisionPointRec (mouse_pos, list))
            {
                int clicked_row = (mouse_pos.y - 100) / 30;

                if (clicked_row >= 0 && clicked_row < view.count)
                {
                    int actual_index = view.indices[clicked_row];
                    task_duration = today_list->items[actual_index]->target_duration;
                    active_task = actual_index;
                    total_seconds = task_duration * 60;
                    remaining_seconds = total_seconds;
                    is_timer_running = false;
                }
            }

            else
            {
               focused_box = 0;
            }

        }

        int key = Engine_GetPressedKey();

        if (key != 0)
        {
            if (key == 27)
            {
                if (focused_box != 0)
                {
                    focused_box = 0;
                    is_edit_mode = false;
                    name_len = 0; memset(name_buffer, 0, sizeof(name_buffer));
                    time_len = 0; memset(time_buffer, 0, sizeof(time_buffer));
                    dur_len = 0;  memset(dur_buffer, 0, sizeof(dur_buffer));
                    rec_len = 0;  memset(rec_buffer, 0, sizeof(rec_buffer));
                }

                else if (active_task != -1)
                {
                    is_timer_running = false;
                    remaining_seconds = 0;
                    active_task = -1;
                }
            }
            if (focused_box == 0 && active_task != -1 )
            {
                if (key == 8) 
                {
                    delete_task(today_list, active_task);
                    save_tasks(today_list, db_file);
                    update_view_cache(today_list, &view, current_wday);
                    active_task = -1;
                    is_timer_running = false;
                    remaining_seconds = 0;
                }

                else if (key == 69 || key == 101)
                {
                    is_edit_mode = true;

                    strncpy(name_buffer, today_list->items[active_task]->name, 119);
                    name_len = strlen(name_buffer);

                    struct tm *edit_time_info = localtime(&today_list->items[active_task]->scheduled_time);
                    strftime(time_buffer, sizeof(time_buffer), "%H:%M", edit_time_info);
                    time_len = strlen(time_buffer);

                    snprintf(dur_buffer, sizeof(dur_buffer), "%d", today_list->items[active_task]->target_duration);
                    dur_len = strlen(dur_buffer);

                    uint8_t mask = today_list->items[active_task]->recurrence_mask;
                    if (mask == 127) 
                    {
                        strncpy(rec_buffer, "D", 2);
                    } 
                    else if (mask > 0) 
                    {
                        strncpy(rec_buffer, "W", 2);
                    }
                    else 
                    {
                        strncpy(rec_buffer, "O", 2);
                    }
                    rec_len = 1;

                    focused_box = 1;
                }
            }
             
            else if (focused_box != 0 )
            {
                if (key == 8)
                {
                    switch (focused_box)
                    {
                        case 1:
                        if (name_len > 0)
                        {
                            name_len--;
                            name_buffer [name_len] = '\0';
                        }
                        break;

                        case 2:
                        if (dur_len > 0)
                        {
                            dur_len--;
                            dur_buffer [dur_len] = '\0';
                        }
                        break;

                        case 3:
                        if (rec_len > 0)
                        {
                           rec_len--;
                           rec_buffer [rec_len] = '\0';
                        }
                        break;

                        case 4:
                        if (time_len > 0)
                        {
                            time_buffer [--time_len] = '\0';
                        }
                        break;

                    }
                }

                else if (key == 10)
                {
                    task_duration = atoi (dur_buffer);

                    uint8_t mask = 0;

                    if (*rec_buffer == 'w' || *rec_buffer == 'W')
                    {
                        mask = (1 << time_info->tm_wday);
                    }

                    else if (*rec_buffer == 'd' || *rec_buffer == 'D')
                    { 
                       mask = 127; 
                    }

                    time_t exact_time = calculate_scheduled_time(get_day_start_time(), time_buffer);

                    if (is_edit_mode && active_task != -1)
                    {
                        strncpy(today_list->items[active_task]->name, name_buffer, 119);
                        today_list->items[active_task]->scheduled_time = exact_time;
                        today_list->items[active_task]->target_duration = task_duration;
                        today_list->items[active_task]->recurrence_mask = mask;
                    
                        is_edit_mode = false;
                    }

                    else
                    {
                        Task *t = create_task(name_buffer, task_duration, exact_time, mask);
                        append_task(today_list, t);
                    }

                    save_tasks(today_list, db_file);
                    update_view_cache(today_list, &view, current_wday);

                    name_len = 0;
                    memset(name_buffer, 0, sizeof(name_buffer));

                    time_len = 0; 
                    memset(time_buffer, 0, sizeof(time_buffer));

                    dur_len = 0;
                    memset(dur_buffer, 0, sizeof(dur_buffer));

                    rec_len = 0;
                    memset(rec_buffer, 0, sizeof(rec_buffer));

                    focused_box = 0;

                }

                else if (key >= 32 && key <= 126)
                {
                    if (focused_box == 1 && name_len < 119)
                    {
                        name_buffer [name_len] = (char)key;
                        name_len++;
                        name_buffer [name_len] = '\0';
                    }

                    else if (focused_box == 2 && dur_len < 15)
                    {
                        dur_buffer [dur_len] = (char) key;
                        dur_len++;
                        dur_buffer [dur_len] = '\0';
                    }

                    else if (focused_box == 3 && rec_len < 15)
                    {
                        rec_buffer [rec_len] = (char) key;
                        rec_len++;
                        rec_buffer [rec_len] = '\0';
                    }

                    else if (focused_box == 4 && time_len < 15)
                    {
                        time_buffer[time_len++] = (char)key; 
                        time_buffer[time_len] = '\0';
                    }
               
                }
            }        
        }
        
        Engine_EndDrawing   ();
 
        usleep(target_time_per_frame);  
    }   

    Engine_CloseWindow     ();

    free_list(today_list);

    return 0;
}
