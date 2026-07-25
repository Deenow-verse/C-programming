#include <stdio.h>

int int_size (void);

int main (void)
{
    printf ("The number of bits contained in an int for my computer is %i\n", int_size ());
    
    return 0;
}

int int_size (void)
{
    int number_of_bits = 0, n;
    n = ~0;

    while (n != 0)
        {
            n <<= 1;
            ++number_of_bits;
        }

    return number_of_bits;
}