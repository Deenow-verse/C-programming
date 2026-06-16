#include <stdio.h>

int main (void)
{
    int n, m;

     printf ("A TABLE OF NUMBERS BETWEEN 1-10 AND THEIR SQUARES\n\n");
        printf ("n              n^2\n");
        printf ("__             _____\n");

    for (n = 1; n <= 10; n++)
    {
        m = n * n;       
        printf ("%i             %i\n", n, m);        
    }

    return 0;

}