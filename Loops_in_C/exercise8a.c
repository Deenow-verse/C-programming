#include <stdio.h>

int main (void)
{
    int n = 1, triangular_number = 0;

    while ( n <= 200)
    {

     triangular_number += n;
     ++n;
    }
     printf ("The 200th triangular number is %i\n", triangular_number);

    return 0;

}