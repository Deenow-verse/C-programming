#include "engine.h"
#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEPTH() DefaultDepth(display, screen) 

Display *display;
Window window;
Pixmap back_buffer;
int screen;
GC gc;
bool should_close = false;
bool needs_resize = false;
int current_width = 0; 
int current_height = 0;

unsigned long _ColorToX11Pixel(RGBA_Colour c)
{
    return (c.r << 16) | (c.g << 8) | c.b;
}

void Engine_InitWindow(int width, int height, const char* title)
{
    current_width = width; 
    current_height = height;

    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    screen = DefaultScreen(display);

    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width, height, 1, BlackPixel(display, screen), WhitePixel(display, screen));

    back_buffer = XCreatePixmap(display, window, width, height, DefaultDepth(display, screen));

    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);

    XStoreName(display, window, title);
    XMapWindow(display, window);

    gc = XCreateGC(display, window, 0, NULL);
}

void Engine_CloseWindow(void) 
{
    XFreeGC(display, gc);
    XFreePixmap(display, back_buffer);
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

        if (event.type == ConfigureNotify)
        {
            int new_width = event.xconfigure.width;    
            int new_height = event.xconfigure.height;

            if (new_width != current_width || new_height != current_height)
            {
                current_width = new_width ;
                current_height = new_height;

                needs_resize = true;
            }
        }
    }

     if (needs_resize)
    {

        XFreePixmap(display, back_buffer);
        back_buffer = XCreatePixmap(display, window, current_width, current_height, DefaultDepth(display, screen));
        needs_resize = false;
    }
    
}

void Engine_EndDrawing(void)
{
    XWindowAttributes wa;
    XGetWindowAttributes(display, window, &wa);
    XCopyArea(display, back_buffer, window, gc, 0, 0, wa.width, wa.height, 0, 0);
    XFlush(display);
}

void Engine_ClearBackground(RGBA_Colour color)
{
    XSetForeground(display, gc, _ColorToX11Pixel(color));
    XWindowAttributes wa;
    XGetWindowAttributes(display, window, &wa);
    XFillRectangle(display, back_buffer, gc, 0, 0, wa.width, wa.height);
}

void Engine_DrawRectangle(int x, int y, int width, int height, RGBA_Colour color)
{
    XSetForeground(display, gc, _ColorToX11Pixel(color));
    XFillRectangle(display, back_buffer, gc, x, y, width, height);
}