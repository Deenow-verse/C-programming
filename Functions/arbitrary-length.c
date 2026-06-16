#include <stdio.h>

int minimum (int values [], int numberofelements)
{
    int minvalue, i;

    minvalue = values [0];
    
    for (i = 1; i < numberofelements; ++i)
    {
        if (values [i] < minvalue)
        minvalue = values [i];
    }

    return minvalue;

}

int main (void)
{
    int array1[5] = { 157, -28, -37, 26, 10 };
    int array2[7] = { 12, 45, 1, 10, 5, 3, 22 };

    int minimum (int values[], int numberOfElements);

    printf ("array1 minimum: %i\n", minimum (array1, 5));
    printf ("array2 minimum: %i\n", minimum (array2, 7));

    return 0;
    
}