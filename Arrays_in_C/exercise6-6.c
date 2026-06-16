#include <stdio.h>


int main (void)
{
    int fibonacci_1, fibonacci_2, fibonacci_3, i;

    fibonacci_1 = 0;
    fibonacci_2 = 1;

    for (i =2; i <= 15; ++i)
    {
        fibonacci_3 = fibonacci_1 + fibonacci_2;
        printf ("%i ", fibonacci_3);
        fibonacci_1 = fibonacci_2;
        fibonacci_2 = fibonacci_3;
    }

    printf ("\n");

    return 0;
}