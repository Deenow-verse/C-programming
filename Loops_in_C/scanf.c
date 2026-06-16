#include <stdio.h>

int main (void)
{
    int n, triangularNumber;
    printf ("What triangular number do you want? ");
    scanf ("%i", &n);
    
    triangularNumber =  0 ;
    for ( int i = 1; i <= n; ++i )
    {
        triangularNumber += i;
    }
    printf ("Triangular number %i is %i\n", n, triangularNumber);
    return 0;
}