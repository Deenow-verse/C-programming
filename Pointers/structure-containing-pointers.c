#include <stdio.h>

int main (void)
{
    struct IntPtr
    {
        int *p1;
        int *p2;
    } Pointers;

    int i1 = 100, i2;

    Pointers.p1 = &i1;
    Pointers.p2 = &i2;
    *Pointers.p2 = -97;

    printf ("i1 = %d  Pointers.p1 = %d \n", i1, *Pointers.p1);
    printf ("i2 = %d  Pointers.p2 = %d \n", i2, *Pointers.p2);

    return 0;

}