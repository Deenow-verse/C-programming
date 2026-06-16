#include <stdio.h>

int main (void)
{
    int number, right_digit;

    printf ("Enter the number to be reversed\n");
    scanf ("%i", &number);

    do  {
        right_digit = number % 10;
        printf ("%i", right_digit);
        number /= 10;        
    }

    while (number != 0);

    printf ("\n");

    return 0;

}