#include <stdio.h>

#define MIN(a,b) (((a) < (b)) ? (a) : (b) )

int main (void)
{
    int j;

    j = MIN (6, 3);
    if (j == 1)
    printf ("The numbers are equal\n");
    else
    printf ("The smallest of the two is %d\n", j);

    j = MIN (6, 6);
    if (j == 1)
    printf ("The numbers are equal\n");
    else
    printf ("The smallest of the two is %d\n", j);

    j = MIN (3, 6);
    if (j == 1)
    printf ("The numbers are equal\n");
    else
    printf ("The smallest of the two is %d\n", j);
}