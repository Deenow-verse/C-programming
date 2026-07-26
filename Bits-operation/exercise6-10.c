#include <stdio.h>

int int_size (void);
int bitPat_Search (unsigned source, unsigned int pattern, int n);

int main (void)
{
    int index;

    index = bitPat_Search (0xe1f4, 0x5, 3);

    if (index == -1)    
    printf ("The Number has not been found in the integer\n");

    else
    printf ("The number has been found to start at %i\n", index);
    

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

int bitPat_Search (unsigned source, unsigned int pattern, int n)
{
    int bit_size = int_size (), i, window, extracted_bits;

    window = (1u << n) - 1;
   
    for (i = 0; i <= bit_size - n; ++i)
    {
        int shift_amount = bit_size - n - i;
        extracted_bits = (source >> shift_amount) & window;

        if ( extracted_bits == pattern)
        return i;       
    }

    return -1;
}