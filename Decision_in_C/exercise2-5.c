#include <stdio.h>

int main (void)
{
    int x, y;

    printf ("Enter two integers\n");
    scanf ("%i %i", &x, &y);

    if (y == 0)
    {
        printf ("Divisor cannot be zero\n");
        return 1;
    }
    

    if (x % y == 0)
        printf  ("%i is a divisor for %i\n", y, x);
    else 
        printf ("%i is not a divisor for %i\n", y, x);
    
    return 0;

}