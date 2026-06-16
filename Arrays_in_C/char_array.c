#include <stdio.h>

int main (void)
{
    char word [] = {'H', 'E', 'L', 'L', 'O', '!'};
    int i;

    for (i = 0; i < 6; ++i)
    printf ("%c", word [i]);

    printf ("\n");

    return 0;
}