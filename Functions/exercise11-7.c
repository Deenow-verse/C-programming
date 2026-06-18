#include <stdio.h>

int main (void)
{
    int  n;

    int SumArray (int n, int array0 [n]);

    printf ("Enter now the elements you want sum for:\n");
    scanf ("%d", &n); 
    
    int original_array [n];

    for ( int i = 0; i < n; ++i)
    {           
        printf ("Enter the element %d:\n", i + 1);
        scanf ("%d", &original_array [i]);         
    
    }

    printf ("The sum of the values of the element of your array is %i \n", SumArray (n, original_array));



}

int SumArray (int n, int array0 [])
{
    int sum = 0;

    for (int i = 0; i < n; ++i )
    {
        sum += array0 [i]; 
    }

    return sum;

}