#include <stdio.h>

typedef struct
{
    int numerator;
    int denominator;
} Fraction;

int main (void)
{
    Fraction myfract;

    myfract.numerator = 1;
    myfract.denominator = 3;

    printf ("The fraction is %i/%i\n", myfract.numerator, myfract.denominator);

    return 0;
}