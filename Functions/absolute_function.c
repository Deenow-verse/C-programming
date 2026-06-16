#include <stdio.h>

float absolutevalue (float number)
{
    if (number < 0)
    number *= -1;

    return number;
}

int main (void)
{
    float f1 = -15.5, f2 = 20, f3 = 5.0;
    int i1 = -716;
    float result;

    result = absolutevalue (f1);
    printf ("result = %.2f\n", result);
    printf ("f1 = %.2f\n", f1);

    result = absolutevalue (f2) + absolutevalue (f3);
    printf ("result = %.2f\n", result);

    result = absolutevalue ((float) i1);
    printf ("result = %.2f\n", result);

    result = absolutevalue (i1);
    printf ("result = %.2f\n", result);

    printf ("%.2f\n", absolutevalue (-6.0) / 4 );

    return 0;


}