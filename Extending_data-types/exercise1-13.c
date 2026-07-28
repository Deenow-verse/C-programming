#include <stdio.h>

int randomNumber(void);

int main (void)
{
    typedef int (*functionPtr) (void);
    functionPtr random_int;

    random_int = randomNumber;     

    printf ("The random number generated is %i\n", random_int () );
    printf("The random number generated is %d\n", random_int());
    printf("The random number generated is %d\n", random_int());
    printf("The random number generated is %d\n", random_int());
}

int randomNumber(void)
 {
    static int seed = 12345;
    seed = (seed * 11035 + 12345) % 32768;
    return seed;
}