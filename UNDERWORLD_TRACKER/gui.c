#include <stdio.h>
#include "engine.h"

int main (void)
{
    Engine_InitWindow (800, 600, "Underworld Tracker");

    RGBA_Colour bg = {20, 20, 20, 255};
    RGBA_Colour paint = {153, 232, 248, 232};

    while (!Engine_WindowShouldClose())
    {
        Engine_BeginDrawing ();

        Engine_ClearBackground (bg);

        Engine_DrawRectangle   (32, 48, 720, 480, paint);

        Engine_EndDrawing   ();
    }       

    Engine_CloseWindow     ();

    return 0;
}
