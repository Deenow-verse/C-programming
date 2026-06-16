#include <stdio.h>

int main (void)
{
    int values [10], index;

    for (index = 0; index < 10; ++index)
    {
        values [index] = 0;
        printf ("values [%d] = %d ",index, values [index] );
    }
    
    return 0;
}