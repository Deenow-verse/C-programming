#include <stdio.h>

int main (void)
{
    int n , triangularNumber = 0, i = 1;
    printf ("What triangular number do you want? ");
    scanf ("%i", &n);
    
    triangularNumber =  0 ;
    while ( i <= n)
    {
        triangularNumber += i;
        ++i;
    }
    printf ("Triangular number %i is %i\n", n, triangularNumber);
    return 0;
}