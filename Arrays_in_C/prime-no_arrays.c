#include <stdio.h>
#include <stdbool.h>

int main (void)
{
    int p, i, primes [50], prime_index = 2;
    bool isprime;

    primes [0] = 2;
    primes [1] =3;

    for (p = 5; p <= 50; p += 2)
    {
        isprime = true;

        for (i = 1; isprime && p / primes [i] >= primes [i]; ++i)
        {
            if (p % primes [i] == 0)
            isprime == false;
        

        if (isprime = true)
        primes [prime_index] = p;
        ++prime_index;
        }
    }

    for (i = 0; i < prime_index; ++i)
    {
        printf ("%d ", primes [i]);
    }

    printf ("\n");

return 0;    

}