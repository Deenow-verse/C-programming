#include "engine.h"
       
#define DEPTH() DefaultDepth(display, screen) 

Display *display;
Window window;
Pixmap back_buffer;
int screen;
GC gc;
XftFont *font;
XftDraw *xft_draw;

bool should_close = false;
bool needs_resize = false;

int current_width = 0; 
int current_height = 0;

int mouse_x = 0;
int mouse_y = 0;
bool mouse_pressed = false;

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

    font = XftFontOpen(display, screen, XFT_FAMILY, XftTypeString, "sans", XFT_SIZE, XftTypeDouble, 12.0,NULL);

    if (font == NULL)
    {
        fprintf (stderr, "No font to load\n");
        exit(1);
    }
    xft_draw = XftDrawCreate(display, back_buffer, DefaultVisual(display, screen), DefaultColormap(display, screen));

    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask | ButtonPressMask | PointerMotionMask);

    XStoreName(display, window, title);
    XMapWindow(display, window);

    XSetWindowBackgroundPixmap(display, window, None);

    gc = XCreateGC(display, window, 0, NULL);
}

void Engine_CloseWindow(void) 
{  
    XftDrawDestroy(xft_draw);
    XftFontClose(display, font);
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
    mouse_pressed = false;

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

        if (event.type == ButtonPress)
        {
            if (event.xbutton.button == 1)
            {
                mouse_pressed = true;
            }
        }

        if (event.type == MotionNotify)
        {
            mouse_x = event.xmotion.x;
            mouse_y = event.xmotion.y;
        }

    }

     if (needs_resize)
    {

        XFreePixmap(display, back_buffer);
        XftDrawDestroy(xft_draw); 
        back_buffer = XCreatePixmap(display, window, current_width, current_height, DefaultDepth(display, screen));
        xft_draw = XftDrawCreate(display, back_buffer, DefaultVisual(display, screen), DefaultColormap(display, screen));
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

int Engine_GetMouseX(void)
{
    return mouse_x;
}

int Engine_GetMouseY(void)
{
    return mouse_y;
}

bool Engine_IsMouseButtonPressed(void)
{
    return mouse_pressed;
}

void Engine_DrawText(int x, int y, const char* text, RGBA_Colour color)
{
    XRenderColor xr_color;

    xr_color.red = color.r <<8; 
    xr_color.green = color.g <<8; 
    xr_color.blue = color.b <<8; 
    xr_color.alpha = color.a <<8; 

    XftColor xft_color;
    XftColorAllocValue(display, DefaultVisual(display, screen), DefaultColormap(display, screen), &xr_color, &xft_color);
    XftDrawStringUtf8(xft_draw, &xft_color, font, x, y, (XftChar8 *)text, strlen(text));
    XftColorFree(display, DefaultVisual(display, screen), DefaultColormap(display, screen), &xft_color);
}