#include <stdio.h>

float absolutevalue (float number)
{
    if (number < 0)
    number *= -1;

    return (number);
}

double squareroot (float number)
{
   // const float epsilon = 0.00001;
    double       guess = 1.0;

    while (absolutevalue ((guess * guess) / (number)) != 1)
        {  guess = (number / guess + guess) / 2;
           printf ("Guess = %f\n", guess); 
        } 

    return guess;

}

int main (void)
{
    printf ("squareroot (2.0) = %f\n", squareroot ( 2.0 ) );
    printf ("squareroot (144.0) = %f\n", squareroot ( 144.0) );
    printf ("squareroot (17.5) = %f\n", squareroot ( 17.5) );
    printf ("squareroot (16) = %f\n", squareroot ( 16.0) );

    return 0;
}