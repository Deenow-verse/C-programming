#include <stdio.h>

int main (void)
{
    int n, triangularNumber, counter, m;

    printf ("Enter the number of triangular numbers to be calculated:");
    scanf ("%i", &m);

    for (counter = 1; counter <= m; ++counter)
    {
        printf ("What triangular number do you want?\n ");
        scanf ("%i", &n);
        
        triangularNumber =  0 ;
        for ( int i = 1; i <= n; ++i )
        {
            triangularNumber += i;
        }
        printf ("Triangular number for %i is %i\n\n", n, triangularNumber);
    }
    return 0;
}