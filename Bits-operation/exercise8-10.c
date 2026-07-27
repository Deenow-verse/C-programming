#include <stdio.h>

int int_size (void);
void bitpat_set (unsigned int *extracted_bits, unsigned int source, int starting_bit, int n );

int main (void)
{
    unsigned int extracted_bits = ~0;

    bitpat_set (&extracted_bits, 0, 2, 5);
    printf ("The contents of the of source transfered to extracted_bits is %x\n", extracted_bits);

    bitpat_set (&extracted_bits, 0x55u, 2, 8);
    printf ("The contents of the of source transfered to extracted_bits is %x\n", extracted_bits);

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

void bitpat_set (unsigned int *extracted_bits, unsigned int source, int starting_bit, int n )
{
    unsigned int shifted_data;
    int window, bit_size, shift_amount;

    bit_size = int_size ();
    window = (1u << n) - 1;
    shift_amount = bit_size - (starting_bit + n);
    shifted_data = (source & window) << shift_amount;
    *extracted_bits = *extracted_bits & ~(window << shift_amount);
    *extracted_bits = *extracted_bits | shifted_data;
}