#include <stdio.h>

int int_size (void);
unsigned int bit_set (unsigned int x, int n);
int bit_test (unsigned int x, int n);

int main(void)
{
    unsigned int x = 10;

    printf("Number of bits = %d\n", int_size());

    printf("Bit 28 = %d\n", bit_test(x, 28));

    x = bit_set(x, 27);

    printf("New value = %u\n", x);

    return 0;
}

int int_size (void)
{
    unsigned int n;
    int number_of_bits = 0;
    n = ~0;

    while (n != 0)
        {
            n <<= 1;
            ++number_of_bits;
        }

    return number_of_bits;
}

int bit_test (unsigned int x, int n)
{
    int bits = int_size ();

    return (x >> (bits - 1 - n)) &1;
}

unsigned int bit_set (unsigned int x, int n)
{
    int bits = int_size ();

    return x | (1u << (bits - 1 - n));
}