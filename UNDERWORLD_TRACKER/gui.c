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
    Rectangle name_box = {240, 40, 400, 40};
    Rectangle dur_box = {660, 40, 100, 40};
    Rectangle rec_box  = {780, 40, 100, 40};

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
    char dur_buffer[16] = {0};
    char rec_buffer[16] = {0};
    int name_len = 0, dur_len = 0, rec_len = 0;
    
    Engine_InitWindow (screen_width, screen_height, "Underworld Tracker");

    time_t start_time = 0;
    int task_duration = 0;
    int total_seconds = task_duration * 60;
    int remaining_seconds = total_seconds;
    int active_task = -1;
    
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

        int heatmap_scores[364] = {0};
        time_t today_midnight = get_day_start_time();

        for (int i = 0; i < 364; i++)
        {
            time_t target = today_midnight - ((363 - i) * 86400);
            heatmap_scores[i] = get_completed_tasks_count(db_file, target);
        }

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
            }
        }

        for (int i = 0; i < today_list->size; ++i)
        {
            int text_y = 100 + (i * 30); 

            char duration_text[32];
            snprintf(duration_text, sizeof(duration_text), "%d mins", today_list->items[i]->target_duration);  

            if (today_list->items[i]->completion_status == true)
            {
                Engine_DrawText (240 + 300, text_y, duration_text, clock_active);
                Engine_DrawText (240, text_y, today_list ->items[i]-> name, clock_active);
            }
            
            else if(i == active_task)
            {
                Engine_DrawText (240 + 300, text_y, duration_text, clock);
                Engine_DrawText (240, text_y, today_list ->items[i]-> name, clock);
            }
            else
            {
                Engine_DrawText (240 + 300, text_y, duration_text, text);              
                Engine_DrawText (240, text_y, today_list ->items[i]-> name, text);
            }
            
        }            

        if (is_timer_running)
        {
            Engine_DrawRectangle   (clock_btn.x, clock_btn.y , clock_btn.width, clock_btn.length, clock_active);
            time_t now = time(NULL);
            double elapsed = difftime(now, start_time);
            remaining_seconds = total_seconds - (int)elapsed;

            if (remaining_seconds <= 0)
            {
                is_timer_running = false; 
                remaining_seconds = total_seconds;  
                
                if (active_task != -1)
                {
                    today_list->items[active_task]->completion_status = true;
                    save_tasks(today_list, db_file);
                }
            }
            else
            {
                int mins = remaining_seconds / 60;
                int secs = remaining_seconds % 60;
                
                char timer_text[16];
                snprintf(timer_text, sizeof(timer_text), "%02d:%02d", mins, secs);
                Engine_DrawText (clock_btn.x + 23, clock_btn.y + 45, timer_text, text);
            }
        }
        else
        Engine_DrawRectangle   (clock_btn.x, clock_btn.y , clock_btn.width, clock_btn.length, clock);

        if (Engine_IsMouseButtonPressed())
        {
            Vector2D mouse_pos = { (float)Engine_GetMouseX(), (float)Engine_GetMouseY() };

            if (CheckCollisionPointRec(mouse_pos, clock_btn))
            {
                if (total_seconds > 0)
                {
                    is_timer_running = !is_timer_running;
                    
                    if (is_timer_running)
                    start_time = time(NULL);
                }
                
            }

            else if (CheckCollisionPointRec(mouse_pos, name_box))
            {
                focused_box = 1;
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
                int list_number;
                list_number = (mouse_pos.y - 100) / 30;

                if (list_number >= 0 && list_number < today_list->size)
                {
                    task_duration = today_list -> items [list_number] -> target_duration;
                    active_task = list_number;
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

        if (focused_box != 0 && key != 0)
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
                }
            }

            else if (key == 10)
            {
                task_duration = atoi (dur_buffer);

                uint8_t mask = 0;

                if (*rec_buffer == 'w' || *rec_buffer == 'W')
                {                   
                    time_t now = get_day_start_time();
                    struct tm *time_info = localtime(&now);
                    mask = (1 << time_info->tm_wday);
                }

                else if (*rec_buffer == 'o' || *rec_buffer == 'O')
                { 
                    mask = 127; 
                }
        
                Task *t = create_task(name_buffer, task_duration, get_day_start_time(), mask);
                append_task(today_list, t);
                save_tasks(today_list, db_file);

                name_len = 0;
                memset(name_buffer, 0, sizeof(name_buffer));

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
               
            }
        }

        Engine_EndDrawing   ();
 
        usleep(target_time_per_frame);  
    }   

    Engine_CloseWindow     ();

    free_list(today_list);

    return 0;
}
