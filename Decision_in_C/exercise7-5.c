#include <stdio.h>

int main (void)
{
    int p, d;
    _Bool isPrime;

    printf ("2 ");
    for ( p = 1; p <= 50; p +=2 ) 
    {
        isPrime = 1;

        for ( d = 1; d < p; d += 2  )
            {
              if ( p % d == 0 && d != 1)
              {isPrime = 0;
               break; }
                
            }

        if ( isPrime != 0 && p != 1 )
        printf ("%i ", p);
    }

    printf ("\n");

return 0;
}