#include <stdio.h>

int main (void)
{
    float x = 2.25, X;
    
   X = 3 * x * x * x - 5 * x * x + 6;
   printf ("The value of 3x^3 -5x^2 + 6 when x is %f is %f\n", x, X );

   return 0;
}