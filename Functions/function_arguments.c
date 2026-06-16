#include <stdio.h>

void CalculateTriangularNumber (int n)
{
    int i, triangularNumber = 0;

    for (i = 1; i <= n; ++i)
    triangularNumber += i;

    printf ("Triangular Number %i is %i\n", n, triangularNumber);
}

int main (void)
{
    CalculateTriangularNumber (10);
    CalculateTriangularNumber (20);
    CalculateTriangularNumber (50);

    return 0;
}