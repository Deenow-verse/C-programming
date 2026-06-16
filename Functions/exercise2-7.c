#include <stdio.h>

float absolutevalue (float number)
{
    if (number < 0)
    number *= -1;

    return (number);
}

float squareroot (float number,float epsilon)
{
   // const float epsilon = 0.00001;
    float       guess = 1.0;

    while (absolutevalue (guess * guess - number) >= epsilon)
        guess = (number / guess + guess) / 2;

    return guess;

}

int main (void)
{
    printf ("squareroot (2.0) = %f at epsilon = 0.00001\n", squareroot ( 2.0, 0.00001 ) );
    printf ("squareroot (144.0) = %f at epsilon = 0.05\n", squareroot ( 144.0, 0.05 ) );
    printf ("squareroot (17.5) = %f at epsilon = 0.00002\n", squareroot ( 17.5, 0.00002 ) );
    printf ("squareroot (16) = %f at epsilon = 0.5\n", squareroot ( 16.0, 0.5 ) );

    return 0;
}