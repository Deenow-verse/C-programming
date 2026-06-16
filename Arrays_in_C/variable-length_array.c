#include <stdio.h>

int main (void)
{
    int i, numfibs;

    printf ("How many fibonacci numbers do you want (between 1 and 75)?\n");
    scanf ("%i", &numfibs);

    if (numfibs < 1 || numfibs > 75)
    {
        printf ("Bad number, sorry!\n");
        return 1;        
    } 

    unsigned long long int fibonacci [numfibs];

    fibonacci [0] = 0;
    fibonacci [1] = 1;

    for (i = 2; i < numfibs; ++i)
        fibonacci [i] = fibonacci [i - 2] + fibonacci [i - 1];
        
    for (i = 0; i < numfibs; ++i)
        printf ("%llu ", fibonacci [i]);
    
    printf ("\n");    
        
    return 0;    
}