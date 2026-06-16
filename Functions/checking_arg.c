#include <stdio.h>

float absolutevalue (float number)
{
    if (number < 0)
    number *= -1;

    return (number);
}

float squareroot (float number)
{
    const float epsilon = 0.00001;
    float       guess = 1.0;

    if (number < 0)
    {
        printf ("Negative argument to squareroot.\n");
        return -1.0;
    }
    
    while (absolutevalue (guess * guess - number) >= epsilon)
        guess = (number / guess + guess) / 2;

    return guess;

}

int main (void)
{
    float squareroot (float number);
    float absolutevalue (float number);

    printf ("squareroot (2.0) = %f\n", squareroot (-2.0));
    printf ("squareroot (144.0) = %f\n", squareroot (-144.0));
    printf ("squareroot (17.5) = %f\n", squareroot (-17.5));
    printf ("squareroot (-16) = %f\n", squareroot (-16));

    return 0;
}