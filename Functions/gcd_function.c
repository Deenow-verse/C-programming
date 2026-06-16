#include <stdio.h>

void calculateGreatestCommonDivisor ( int u,int v )
{
    int temp;

    printf ("The GCD of %i and %i is ", u, v);

    while ( v != 0)
    {
        temp = u % v;
        u = v;
        v = temp;
    }

    printf ("%i\n", u);

}

int main (void)
{
    calculateGreatestCommonDivisor (150, 35);
    calculateGreatestCommonDivisor (35, 150);
    calculateGreatestCommonDivisor (1026, 405);
    calculateGreatestCommonDivisor (83, 240);

    return 0;

}