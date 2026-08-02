#include <stdio.h>

int main (void)
{
    int i, j;
    int left_channel [] = {10, 20, 30, 40, 50, 60};
    int right_channel [] = {1, 2, 3, 4, 5, 6};
    int mixed_channel [6] = {0};

    printf ("The Dual-Buffered merged Audio stream is: \n");

    for ( i = 0, j = 5; i < 6; i++, j--)
    mixed_channel[i] = left_channel[i] + right_channel[j] ,printf ("%d\t", mixed_channel[i]);

    printf ("\n");

    return (0);

}
