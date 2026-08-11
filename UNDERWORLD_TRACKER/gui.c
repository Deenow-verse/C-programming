#include <unistd.h>
#include "engine.h"

int main (void)
{
    int target_time_per_frame = 16666;
    Engine_InitWindow (800, 600, "Underworld Tracker");

    RGBA_Colour bg = {20, 20, 20, 255};
    RGBA_Colour paint = {153, 232, 248, 232};

    while (!Engine_WindowShouldClose())
    {
        Engine_BeginDrawing ();

        Engine_ClearBackground (bg);

        Engine_DrawRectangle   (32, 48, 720, 480, paint);

        Engine_EndDrawing   ();

        usleep(target_time_per_frame);
    }       

    Engine_CloseWindow     ();

    return 0;
}
