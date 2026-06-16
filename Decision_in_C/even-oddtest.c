#include <stdio.h>

int main (void)
{
    int number_to_test, remainder;

    printf ("Enter your numberto test: ");
    scanf ("%d", &number_to_test);

    remainder = number_to_test % 2;

    if (remainder == 0)
        printf ("The number %d is even.\n", number_to_test);
    else 
        printf ("The number %d is odd.\n,", number_to_test);

    return 0;
}