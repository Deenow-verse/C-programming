#include <stdio.h>

int main (void)
{
    int counter = 10, x;
    int *int_ptr;

    int_ptr = &counter;
    x = *int_ptr;

    printf ("counter = %d   x = %d\n", counter, x);
    return 0;
}