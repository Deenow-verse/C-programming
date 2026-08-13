#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_math.h"
#include <X11/Xft/Xft.h>
#include <X11/Xutil.h>
#include <X11/Xlib.h>

void Engine_InitWindow(int width, int height, const char* title);

void Engine_CloseWindow(void);

bool Engine_WindowShouldClose(void);

void Engine_BeginDrawing(void);

void Engine_EndDrawing(void);

void Engine_ClearBackground(RGBA_Colour color);

void Engine_DrawRectangle(int x, int y, int width, int height, RGBA_Colour color);

int Engine_GetMouseX(void);

int Engine_GetMouseY(void);

bool Engine_IsMouseButtonPressed(void);

void Engine_DrawText(int x, int y, const char* text, RGBA_Colour color);

#endif