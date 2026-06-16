#include <stdio.h>

int main (void)
{
    int n, triangular_number;
    triangular_number = 0;

    for(n = 1; n <= 200; n += 1){

     triangular_number += n;
     printf ("%-2i                  %i\n", n, triangular_number);
    }
     
    return 0;

}