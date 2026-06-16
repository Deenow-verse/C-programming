#include <stdio.h>

int main (void)
{
    const char base_digits [16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    int convertedNumber [64];
    long int numberToConvert;
    int next_digit, base, index = 0;

    printf ("Enter the number to be converted\n");
    scanf ("%ld", &numberToConvert);
    printf ("Enter the base you want your number to be converted to\n");
    scanf ("%i", &base);

    do
    {
        convertedNumber [index] = numberToConvert % base;
        ++index;
        numberToConvert /= base;
    }

    while ( numberToConvert != 0 );
    
    printf ("converted number = ");

    for (--index; index >= 0; --index)
    
    {
        next_digit = convertedNumber [index];
        printf ("%c", base_digits [next_digit]);
    }

    printf ("\n");
    
    return 0;
    
}