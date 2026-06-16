#include <stdio.h>

int main (void)
{
    int i = 256, j = 7, next_multiple;
    
    next_multiple = i + j - i % j; 
    printf("The next largest Number of days from %d divided by %i days that is a multiple of %d is %d\n", i, j, j, next_multiple);

    return 0;
}