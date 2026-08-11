#include "engine.h"
#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Display *display;
Window window;
int screen;
GC gc;
bool should_close = false;

unsigned long _ColorToX11Pixel(RGBA_Colour c)
{
    return (c.r << 16) | (c.g << 8) | c.b;
}

void Engine_InitWindow(int width, int height, const char* title)
{
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    screen = DefaultScreen(display);

    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width, height, 1, BlackPixel(display, screen), WhitePixel(display, screen));

    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    XSelectInput(display, window, ExposureMask | KeyPressMask);

    XStoreName(display, window, title);
    XMapWindow(display, window);

    gc = XCreateGC(display, window, 0, NULL);
}

void Engine_CloseWindow(void) 
{
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

bool Engine_WindowShouldClose(void)
{
    return should_close;
}

void Engine_BeginDrawing(void)
{
    XEvent event;

    while (XPending(display) > 0)
    {
        XNextEvent(display, &event);

        if (event.type == ClientMessage)
        {
            should_close = true;
        }
    }
}

void Engine_EndDrawing(void)
{
    XFlush(display);
}

void Engine_ClearBackground(RGBA_Colour color)
{
    XSetForeground(display, gc, _ColorToX11Pixel(color));
    XWindowAttributes wa;
    XGetWindowAttributes(display, window, &wa);
    XFillRectangle(display, window, gc, 0, 0, wa.width, wa.height);
}

void Engine_DrawRectangle(int x, int y, int width, int height, RGBA_Colour color)
{
    XSetForeground(display, gc, _ColorToX11Pixel(color));
    XFillRectangle(display, window, gc, x, y, width, height);
}