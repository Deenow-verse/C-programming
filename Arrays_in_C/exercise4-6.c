#include <stdio.h>

int main (void)
{
    float award [10], average, sum = 0.0;

    printf ("Enter the value given by the test to find the average result:\n");
    for (int i = 0; i < 10; ++i)
    {        
        scanf ("%f", &award [i]);
        sum += award [i];
    }
    average = sum / 10;
    

    printf ("The average award is: %.2f\n", average);

    return 0;

}