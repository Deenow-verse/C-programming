#include <stdio.h>

int main (void)
{
    int n, triangularNumber, counter;

    for (counter = 1; counter <= 5; ++counter)
    {
        printf ("What triangular number do you want?\n ");
        scanf ("%i", &n);
        
        triangularNumber =  0 ;
        for ( int i = 1; i <= n; ++i )
        {
            triangularNumber += i;
        }
        printf ("Triangular number %i is %i\n\n", n, triangularNumber);
    }
    return 0;
}