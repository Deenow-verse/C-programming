#include <unistd.h>
#include "engine.h"

int main (void)
{
    int target_time_per_frame = 16666;
    Engine_InitWindow (800, 600, "Underworld Tracker");

    RGBA_Colour bg = {255, 255, 255, 255};
    RGBA_Colour center = {198, 228, 255, 255};
    RGBA_Colour clock = {246, 114, 56, 255  };
    RGBA_Colour grid = {236, 236, 242, 255};
    RGBA_Colour square ={56, 139, 253, 255};
    RGBA_Colour sidebar = {219, 109, 40, 255};

    while (!Engine_WindowShouldClose())
    {
        Engine_BeginDrawing ();

        Engine_ClearBackground (bg);

        Engine_DrawRectangle   (0, 0, 210, 1000, sidebar);

        Engine_DrawRectangle   (700, 720, 900, 240, center);

        Engine_DrawRectangle   (725, 745 , 90, 90, clock);

        Engine_DrawRectangle   (896, 854, 692, 94, grid);

        for (int row = 861; row  < 945; row += 13)
        {
            for (int column = 903; column < 1574; column += 13)
            {
                Engine_DrawRectangle (column, row, 5, 5, square);
            }
        }

        Engine_EndDrawing   ();

        usleep(target_time_per_frame);
    }       

    Engine_CloseWindow     ();

    return 0;
}
