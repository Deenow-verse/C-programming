#include <stdio.h>

int main (void)
{
    void exchange (int *pint1, int *pint2);
    int i1 = -5, i2 = 66, *p1 = &i1, *p2 = &i2;

    printf ("i1 = %d  and  i2 = %d\n", i1, i2);

    exchange (p1, p2);
    printf ("i1 = %d  and  i2 = %d\n", i1, i2);

    exchange (&i1, &i2);
    printf ("i1 = %d  and  i2 = %d\n", i1, i2);

    return 0;
}

void exchange (int *pint1, int *pint2)
{
    int temp;

    temp = *pint1;
    *pint1 = *pint2;
    *pint2 = temp; 
}