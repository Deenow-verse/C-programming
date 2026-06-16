#include <stdio.h>

int main (void)
{
    int n, triangular_number;
    triangular_number = 0;

    for(n = 1; n <= 200; n += 1){

     triangular_number += n;
    }
     printf ("The 200th triangular number is %i\n", triangular_number);

    return 0;

}