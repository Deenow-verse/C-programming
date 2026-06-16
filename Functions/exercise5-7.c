#include <stdio.h>

float absolutevalue (float number)
{
    if (number < 0)
    number *= -1;

    return (number);
}

long double squareroot (long double number)
{
   const long double epsilon = 0.0000000000000000000000001L;
   long double       guess = 1.0L;

    while (absolutevalue ((guess * guess) / (number)) != 1)
        {  guess = (number / guess + guess) / 2;
           printf ("Guess = %Lf\n", guess); 
        } 

    return guess;

}

int main (void)
{
    printf ("squareroot (2.0) = %Lf\n", squareroot ( 2.0L ) );
    printf ("squareroot (144.0) = %Lf\n", squareroot ( 144.0L) );
    printf ("squareroot (17.5) = %Lf\n", squareroot ( 17.5L) );
    printf ("squareroot (16) = %Lf\n", squareroot ( 16.0L) );

    return 0;
}