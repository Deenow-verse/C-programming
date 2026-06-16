#include <stdio.h>

int main (void)
{
    int n, m = 1;
    
    printf ("A TABLE OF THE FIRST 10 FACTORIAL\n\n");
    printf ("Number                        Factorial\n");
    printf ("______                        _________\n");

    for (n = 1; n <= 10; n++)
    {
        m *= n;
    printf ("%2i                               %i \n", n, m); 
    }

    return 0;
    
}