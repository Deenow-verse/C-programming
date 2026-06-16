#include <stdio.h>

int main (void)
{
    int number, right_digit;
    printf ("Enter your number.\n");
    scanf ("%d", &number);
    do {

        if (number < 0)
        {   number *= -1;
            right_digit = number % 10;
            number /= 10;
            printf ("-%i",right_digit);}

        else
        {
            right_digit = number % 10;
            printf ("%i", right_digit);
            number = number / 10;}

       }

    while ( number != 0 );
        printf ("\n");

return 0;

}