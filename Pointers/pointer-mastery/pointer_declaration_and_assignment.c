#include <stdio.h>

int main (void)
{
    int i;
    int *p;

    p = &i;

    printf ("the value the pointer is holding is %p which is the address of our i\n", p);

    return 0;
}