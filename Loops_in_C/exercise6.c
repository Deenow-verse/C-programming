#include <stdio.h>

int main (void)
{
    int dollar, cent, counts;

    for (counts = 1; counts <= 10; ++counts)
    {
        printf ("Enter dollars:");
        scanf ("%i", &dollar);
        printf ("Enter cents:");
        scanf ("%i", &cent);

        printf ("$%i.%.2i\n\n", dollar, cent);

    }

    return 0;

}