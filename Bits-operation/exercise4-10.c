#include <stdio.h>

unsigned int rotate (unsigned int value, int n);
int int_size (void);

int main (void)
{
    unsigned int w1 = 0xabcdef00u, w2 = 0xffff1122u;
    
    printf ("%x\n", rotate (w1, 8));
    printf ("%x\n",rotate (w1, -16));
    printf ("%x\n", rotate (w2, 4));
    printf ("%x\n", rotate (w2, -2));
    printf ("%x\n", rotate (w1, 0));
    printf ("%x\n",rotate (w1, 44));

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

unsigned int rotate (unsigned int value, int n)
{
    unsigned int result, bits,word_size;

    word_size = int_size ();
    if (n > 0)
    n %= word_size;

    else
    n = - (-n % word_size);

    if (n == 0)
    result = value;

    else if (n > 0)
    {
        bits = value >> (word_size - n);
        result = value << n | bits;
    }

    else 
    {
        n = -n;
        bits = value << (word_size - n);
        result = value >> n | bits;
    }

    return result;
}