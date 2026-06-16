#include <stdio.h>

int CalculateTriangularNumber (int n)
{
    int i, triangularNumber = 0;

    for (i = 1; i <= n; ++i)
    triangularNumber += i;

    printf ("Triangular Number %i is %i\n", n, triangularNumber);

    return triangularNumber;
}

int main (void)
{
    int counter, n;
    int CalculateTriangularNumber (int n);

    for ( counter = 1; counter <= 5; ++counter ) 
    {
        printf ("What triangular number do you want?\n");
        scanf ("%i", &n);

        CalculateTriangularNumber (n);
    }
    
    return 0;
}