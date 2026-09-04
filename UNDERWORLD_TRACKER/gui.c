#include "engine.h"
#include "my_math.h"
#include "tracker.h"

int main (void)
{
    int screen_width = Engine_GetScreenWidth();
    int screen_height = Engine_GetScreenHeight();

    int target_time_per_frame = 16666;

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

    double camera_y = 0.0;
    double target_camera_y = 0.0;
    int scroll_speed = 40;
    
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

    double previous_time = Engine_GetTime();

    while (!Engine_WindowShouldClose())
    {
        
        Engine_BeginDrawing ();

        double current_time = Engine_GetTime();

        float dt = current_time - previous_time;

        camera_y = Lerp(camera_y, target_camera_y, 15.0f * dt);

        previous_time = current_time;

        int win_w = current_width;
        int win_h = current_height;

        double dynamic_font_size = (win_w + win_h) * 0.005;

        if (dynamic_font_size < 5.0) 
        dynamic_font_size = 5.0;

        Engine_SetFontSize(dynamic_font_size);

        float sidebar_pct = 0.11f; 
        float top_gap_pct = 0.05f;  
        float box_height_pct = 0.045f;

        int sidebar_w = (int)(win_w * sidebar_pct);
        int list_x = sidebar_w;
        int list_w = win_w - sidebar_w;

        int content_margin = (int)(win_w * 0.04f); 
        int content_start_x = list_x + content_margin;

        int box_gap = (int)(win_w * 0.015f);

        int name_w = (int)(win_w * 0.20f); 
        int time_w = (int)(win_w * 0.06f); 
        int dur_w  = (int)(win_w * 0.06f); 
        int rec_w  = (int)(win_w * 0.06f);

        int top_y = (int)(win_h * top_gap_pct);
        int box_h = (int)(win_h * box_height_pct);
    
        int clock_size = (int)(win_h * 0.08f);
        int clock_x = win_w - clock_size - content_margin;
        Rectangle clock_btn = { (float)clock_x, (float)top_y, (float)clock_size, (float)clock_size };

        Rectangle name_box = { (float)content_start_x, (float)top_y, (float)name_w, (float)box_h };
        Rectangle time_box = { name_box.x + name_w + box_gap, (float)top_y, (float)time_w, (float)box_h };
        Rectangle dur_box  = { time_box.x + time_w + box_gap, (float)top_y, (float)dur_w,  (float)box_h };
        Rectangle rec_box  = { dur_box.x + dur_w + box_gap,   (float)top_y, (float)rec_w,  (float)box_h };

        Rectangle list = { (float)list_x, 0, (float)list_w, (float)win_h };
   
        int text_pad_x = (int)(win_w * 0.008f);
        int text_baseline_offset = (int)(box_h * 0.68f); 

        int list_start_y = top_y + clock_size + (int)(win_h * 0.04f);
        int row_height = (int)(win_h * 0.028f);

        Engine_ClearBackground (bg);

        Engine_DrawRectangle(0, 0, sidebar_w, win_h, sidebar);

        Engine_DrawRectangle(list.x, list.y, list.width, list.length , center);

        // Name Box
        Engine_DrawRectangle(name_box.x, name_box.y, name_box.width, name_box.length, focused_box == 1 ? clock_active : center);
        Engine_DrawText(name_box.x + text_pad_x, name_box.y + text_baseline_offset, name_buffer, text);
        if (name_len == 0 && focused_box != 1)
        {
            Engine_DrawText(name_box.x + text_pad_x, name_box.y + text_baseline_offset, "Task Name...", text);
        }

        // Time Box
        Engine_DrawRectangle(time_box.x, time_box.y, time_box.width, time_box.length, focused_box == 4 ? clock_active : center);
        Engine_DrawText(time_box.x + text_pad_x, time_box.y + text_baseline_offset, time_buffer, text);
        if (time_len == 0 && focused_box != 4)
        {
            Engine_DrawText(time_box.x + text_pad_x, time_box.y + text_baseline_offset, "HH:MM", text);
        }

        // Duration Box
        Engine_DrawRectangle(dur_box.x, dur_box.y, dur_box.width, dur_box.length, focused_box == 2 ? clock_active : center);
        Engine_DrawText(dur_box.x + text_pad_x, dur_box.y + text_baseline_offset, dur_buffer, text);
        if (dur_len == 0 && focused_box != 2)
        {
            Engine_DrawText(dur_box.x + text_pad_x, dur_box.y + text_baseline_offset, "Mins", text);
        }

        // Recurrence Box
        Engine_DrawRectangle(rec_box.x, rec_box.y, rec_box.width, rec_box.length, focused_box == 3 ? clock_active : center);
        Engine_DrawText(rec_box.x + text_pad_x, rec_box.y + text_baseline_offset, rec_buffer, text);
        if (rec_len == 0 && focused_box != 3) 
        {
            Engine_DrawText(rec_box.x + text_pad_x, rec_box.y + text_baseline_offset, "D/W/O", text);
        }       

        int box_size = (int)(win_h * 0.012f);
        int grid_padding = (int)(win_h * 0.004f);
        int total_cols = 52;
        int total_rows = 7;

        int grid_width = total_cols * (box_size + grid_padding);
        int grid_height = total_rows * (box_size + grid_padding);

        int start_x = content_start_x;
        int start_y = win_h - grid_height - (int)(win_h * 0.067f);

        bool render_tooltip = false;
        char tooltip_text[64] = {0};
        Vector2D tooltip_pos = {0};
        Vector2D mouse_pos = { (float)Engine_GetMouseX(), (float)Engine_GetMouseY() };

        for (int col = 0; col < total_cols; col++)
        {
            for (int row = 0; row < total_rows; row++)
            {
                int x = start_x + col * (box_size + grid_padding);
                int y = start_y + row * (box_size + grid_padding);
                
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
            int tip_width = (int)(win_w * 0.14f);
            int tip_height = (int)(win_h * 0.025f);
            int tip_x = tooltip_pos.x - (tip_width / 2);
            int tip_y = tooltip_pos.y - tip_height - 8;

            Engine_DrawRectangle(tip_x, tip_y, tip_width, tip_height, text);
            Engine_DrawText(tip_x + (int)(tip_width * 0.05f), tip_y + (int)(tip_height * 0.7f), tooltip_text, bg);
        }

        int visible_list_height = (int)(win_h * 0.75f) - list_start_y;
        int max_target_y = (view.count * row_height) - visible_list_height;

        if (max_target_y < 0) 
        max_target_y = 0;

        if (target_camera_y > max_target_y) 
        {
            camera_y = max_target_y;
        }

        if (camera_y < 0) 
        {
            target_camera_y = 0;
        }

        for (int v = 0; v < view.count; ++v)
        {
            int actual_index = view.indices[v];

            int row_top_y = list_start_y + (v * row_height) - (int) camera_y;

            if (row_top_y + row_height < list_start_y)
            {
                continue; 
            }

            if (row_top_y > (win_h * 0.75f)) 
            break;

            int text_y = row_top_y + (int)(row_height * 0.75f); 

            if (text_y < list_start_y) 
            {
                continue; 
            }

            if (text_y > (win_h * 0.75f)) 
            {
                break; 
            }

            char duration_text[32];
            snprintf(duration_text, sizeof(duration_text), "%d mins", today_list->items[actual_index]->target_duration);  

            char sched_time_text[16];
            struct tm *sched_info = localtime(&today_list->items[actual_index]->scheduled_time);
            strftime(sched_time_text, sizeof(sched_time_text), "%H:%M", sched_info);

            RGBA_Colour current_color = text;
            if (today_list->items[actual_index]->completion_status == true) current_color = clock_active;
            else if (actual_index == active_task) current_color = clock;

            Engine_DrawText (name_box.x + text_pad_x, text_y, today_list->items[actual_index]->name, current_color);
            Engine_DrawText (time_box.x + text_pad_x, text_y, sched_time_text, current_color); 
            Engine_DrawText (dur_box.x + text_pad_x,  text_y, duration_text, current_color);
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

                    char notify_cmd[512];

                    snprintf(notify_cmd, sizeof(notify_cmd), "notify-send -u critical -i clock \"Underworld Tracker\" \"Time is up! Task completed: %s\"", today_list->items[active_task]->name);

                    int sys_ret = system(notify_cmd);
                    (void)sys_ret;
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
            Engine_DrawText(clock_btn.x + (int)(clock_btn.width * 0.22f), clock_btn.y + (int)(clock_btn.length * 0.57f), timer_text, text);
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
                Engine_DrawText(clock_btn.x + (int)(clock_btn.width * 0.22f), clock_btn.y + (int)(clock_btn.length * 0.57f), timer_text, text);
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
                        if (remaining_seconds <= 0) 
                        {
                            remaining_seconds = total_seconds;
                        }
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
                if (mouse_pos.y < list_start_y)
                {
                    focused_box = 0;
                }
                
                else
                {
                    int clicked_row = ((int)mouse_pos.y - list_start_y + (int)camera_y) / row_height;

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
            }

            else
            {
               focused_box = 0;
            }

        }

        int key = Engine_GetPressedKey();

        if (key != 0)
        {
            if (key == 65362 || key == 65365)
            {
                target_camera_y -= scroll_speed;
                if (target_camera_y < 0) 
                {
                    target_camera_y = 0;
                }
            }
            else if (key == 65364 || key == 65366)
            {
                target_camera_y += scroll_speed;
            }
            
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
                    
                    sort_tasks(today_list);

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
