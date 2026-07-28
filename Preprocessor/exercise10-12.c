#include <stdio.h>

#define printint(n) printf ("%i\n", x ## n)
#define printx(n) printint(x ## n)
#define ASSIGN(n) (xx ## n)

int main (void)
{    
    int i = 0, xxi, x0 = 1;

    for (i = 1; i < 100; ++i)
    {
        ASSIGN (i) = ASSIGN (i - 1);
    }

    for (i = 0; i < 100; ++i)
    {
        printx (i);
    }
}