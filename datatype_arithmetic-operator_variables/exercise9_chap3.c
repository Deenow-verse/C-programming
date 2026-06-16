#include <stdio.h>

int main (void)
{
    int i , j , next_multiple;
    
    i = 365;
    j = 7;
    next_multiple = i + j - i % j; 
    printf("The next largest Number of days from %d divided by %i days that is a multiple of %d is %d\n", i, j, j, next_multiple);

    i = 12258;
    j = 23;
    next_multiple = i + j - i % j; 
    printf("The next largest Number of days from %d divided by %i days that is a multiple of %d is %d\n", i, j, j, next_multiple);

    i = 996;
    j = 4;
    next_multiple = i + j - i % j; 
    printf("The next largest Number of days from %d divided by %i days that is a multiple of %d is %d\n", i, j, j, next_multiple);


    return 0;
}