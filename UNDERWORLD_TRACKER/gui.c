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
    Rectangle input_box = {240, 40, 600, 40};

    list.width =screen_width - 210;
    list.length = screen_height;
    list.x = 210;
    list.y = 0;

    clock_btn.width = 90;
    clock_btn.length = 90;
    clock_btn.x = screen_width - clock_btn.width - 50;
    clock_btn.y =  50;

    bool is_timer_running = false;

    bool is_typing = false;
    char input_buffer[120] = {0};
    int input_length = 0;
    
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

        Engine_DrawRectangle(input_box.x, input_box.y, input_box.width, input_box.length, is_typing ? clock_active : center);

        Engine_DrawText(input_box.x + 10, input_box.y + 25, input_buffer, text);

        if (input_length == 0 && !is_typing)
        {
             Engine_DrawText(input_box.x + 10, input_box.y + 25, "Click here to add a new task...", text);
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

       /* Engine_DrawRectangle   (896, 854, 692, 94, grid);

        for (int row = 861; row  < 945; row += 13)
        {
            for (int column = 903; column < 1574; column += 13)
            {
                Engine_DrawRectangle (column, row, 5, 5, square);
            }
        } */

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

            else if (CheckCollisionPointRec(mouse_pos, input_box))
            {
                is_typing = true;
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
               is_typing = false;
            }

        }

        int key = Engine_GetPressedKey();

        if (is_typing && key != 0)
        {
            if (key == 8 && input_length > 0)
            {
                input_length--;
                input_buffer[input_length] = '\0';
            }

            else if (key == 10 && input_length > 0)
            {
        
                Task *t = create_task(input_buffer, 25, get_day_start_time(), 0);
                append_task(today_list, t);
                save_tasks(today_list, db_file);

                input_length = 0;
                memset(input_buffer, 0, sizeof(input_buffer));
                is_typing = false;
            }

            else if (key >= 32 && key <= 126 && input_length < 119)
            {
               input_buffer[input_length] = (char)key;
               input_length++;
               input_buffer[input_length] = '\0';
            }
        }

        Engine_EndDrawing   ();
 
        usleep(target_time_per_frame);  
    }   

    Engine_CloseWindow     ();

    free_list(today_list);

    return 0;
}
