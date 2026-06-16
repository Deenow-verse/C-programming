#include <stdio.h>

int main (void)
{
    int power, number;
    long int X_to_the_n (int x, int n);
    printf ("Enter the number and the power you want to raise that number to\n");
    scanf ("%d  %d", &number, &power);

    printf ("%d raised to %i is %ld\n", number, power, X_to_the_n (number, power) );

    return 0;
}

long int X_to_the_n (int x, int n)
{
    int i, compound = x;

    for (i = 1; i < n; ++i)
    {
        compound *= x;
    }

    return compound;

}