#include <stdio.h>
#define DEBUG

int process (int i, int j, int k);

int main (void)
{
    int i, j, k, nread;

    nread = scanf("%i  %i  %i", &i, &j, &k);

    #ifdef DEBUG
    fprintf (stderr, "Number of intergers read = %i\n", nread);

    fprintf (stderr, "i = %i\t j = %i\t  k = %i\n", i, j, k);

    #endif

    printf ("%i\n", process(i, j, k));

    return 0;
    
}

int process (int i, int j, int k)
{
    return i + j + k;
}