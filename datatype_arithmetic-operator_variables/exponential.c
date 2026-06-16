#include <stdio.h>

int main (void)
{
    float j;

    j = (3.31 * 10e-8 * 2.01 * 10e-7) / (7.16 * 10e-6 + 2.01 * 10e-8);
    printf ("The result of (3.31 x 10-8 x 2.01 x 10-7) / (7.16 x 10-6 + 2.01 x 10-8) is %f\n", j);
    
    return 0;
}