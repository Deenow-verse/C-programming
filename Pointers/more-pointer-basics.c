#include <stdio.h>

int main(void)
{
    char c = 'Q';
    char *char_ptr;
    
    char_ptr = &c;

    printf ("%c  %c\n", c, *char_ptr);

    c = '/';
    printf ("%c  %c\n", c, *char_ptr);

    *char_ptr = ')';
    printf ("%c  %c\n", c, *char_ptr);

    return 0;
}