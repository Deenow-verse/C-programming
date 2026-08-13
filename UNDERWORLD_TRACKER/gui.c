#include "engine.h"
#include "my_math.h"
#include "tracker.h"

int main (void)
{
    int screen_width = 1920;
    int screen_height = 1080;

    int target_time_per_frame = 16666;
    Rectangle clock_btn;
    clock_btn.width = 90;
    clock_btn.length = 90;
    clock_btn.x = screen_width - clock_btn.width - 50;
    clock_btn.y =  50;
    bool is_timer_running = false;
    Engine_InitWindow (screen_width, screen_height, "Underworld Tracker");
    time_t start_time = 0;
    int total_seconds = 25 * 60;
    int remaining_seconds = total_seconds;
    
    RGBA_Colour bg = {255, 255, 255, 255};
    RGBA_Colour center = {198, 228, 255, 255};
    RGBA_Colour clock = {246, 114, 56, 255  };
    RGBA_Colour clock_active = {46, 204, 113, 255};
    RGBA_Colour grid = {236, 236, 242, 255};
    RGBA_Colour square ={56, 139, 253, 255};
    RGBA_Colour sidebar = {219, 109, 40, 255};
    RGBA_Colour text = {0, 0, 0, 255};

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

        Engine_DrawRectangle(210, 0, screen_width - 210, screen_height, center);

        for (int i = 0; i < today_list->size; ++i)
        {
            int text_y = 100 + (i * 30); 
            Engine_DrawText (240, text_y, today_list ->items[i]-> name, text);

            char duration_text[32];
            snprintf(duration_text, sizeof(duration_text), "%d mins", today_list->items[i]->target_duration);
            Engine_DrawText (240 + 300, text_y, duration_text, text);
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
            }
            else
            {
                printf("Time remaining: %d\r", remaining_seconds);
                fflush(stdout);
            }
        }
        else
        Engine_DrawRectangle   (clock_btn.x, clock_btn.y , clock_btn.width, clock_btn.length, clock);

        Engine_DrawRectangle   (896, 854, 692, 94, grid);

        for (int row = 861; row  < 945; row += 13)
        {
            for (int column = 903; column < 1574; column += 13)
            {
                Engine_DrawRectangle (column, row, 5, 5, square);
            }
        }

        if (Engine_IsMouseButtonPressed())
        {
            Vector2D mouse_pos = { (float)Engine_GetMouseX(), (float)Engine_GetMouseY() };
            
            if (CheckCollisionPointRec(mouse_pos, clock_btn))
            {
                is_timer_running = !is_timer_running;

                if (is_timer_running)
                start_time = time(NULL);
            }
        }

        Engine_EndDrawing   ();
 
        usleep(target_time_per_frame);  
    }   

    Engine_CloseWindow     ();

    return 0;
}
