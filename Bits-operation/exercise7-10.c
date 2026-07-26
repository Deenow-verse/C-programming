#include <stdio.h>

int int_size (void);
int bitPat_Search (unsigned source, unsigned int pattern, int n);
int bit_get (unsigned int source, int start_bit, int n);

int main (void)
{
    int start_bit, extracted_bit;

    start_bit = bitPat_Search (0xe1f4, 0x5, 3);
    if (start_bit == -1)
    printf ("The Number has not been found in the source integer\n");

    else
    {
        extracted_bit = bit_get (0xe1f4, start_bit, 3);
        printf ("The extracted bits is %i\n", extracted_bit);
    }   

    extracted_bit = bit_get(0xe1f4, 16, 3);
    printf ("The extracted bits is %i\n", extracted_bit);

    extracted_bit = bit_get(0xe1f4, 19, 5);
    printf ("The extracted bits is %i\n", extracted_bit);
    
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

int bit_get (unsigned int source, int start_bit, int n)
{
    int extracted_bits, window, bit_size;

    bit_size = int_size ();
    window = (1u << n) - 1;
    extracted_bits = (source >> (bit_size - (start_bit + n)) )& window;

    return extracted_bits;
}