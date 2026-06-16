#include <stdio.h>

int main (void)
{
    int digit , sum = 0, number, original_number;

    printf ("Enter the number you want to find the sum of its digit:");
    scanf ("%i", &original_number);
    
    number = original_number;
    while (number != 0 )
    {
        digit = number % 10;
        sum += digit;
        number /= 10;
    }

    printf ("The sum of the digits of the number %i is %i\n", original_number,sum);

    return 0;

}