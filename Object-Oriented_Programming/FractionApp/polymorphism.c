#include <stdio.h>

struct Widget
{
    char name [32];
    void (*draw)(struct Widget *self);
};

void draw_button(struct Widget *self);
void draw_textbox(struct Widget *self);

int main (void)
{
    struct Widget ui_elements[2] =
    {
        {"Submit", draw_button},
        {"Username", draw_textbox}
    };

    for (int i = 0; i < 2; i++)
    {
        ui_elements[i].draw(&ui_elements[i]);
    }

    return 0;
}

void draw_button(struct Widget *self)
{
    printf ("[BUTTON] Rendering button: <%s>\n", self -> name);
}

void draw_textbox(struct Widget *self)
{
    printf ("[TEXTBOX] Rendering textbox: <name>", self -> name);
}

