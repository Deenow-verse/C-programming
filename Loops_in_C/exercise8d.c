#include <stdio.h>

int main (void)
{
    int n, triangularNumber, counter = 1;

    while (counter <= 5)
    {
        triangularNumber = 0; 
        int i = 1;
        printf ("What triangular number do you want?\n ");
        scanf ("%i", &n);
     
        while (i <= n )
        {
            triangularNumber += i;
            ++i;
        }
        printf ("Triangular number %i is %i\n\n", n, triangularNumber);
        ++counter;
    }
    return 0;
}