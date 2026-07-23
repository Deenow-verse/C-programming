#include <stdio.h>

void sort (int *values, int *n)
{
    int *values2, temp;
    int *const arrayEnd = values + *n;

    for (values; values < arrayEnd - 1; ++values)
    {
        for (values2 = values + 1; values2 < arrayEnd ; ++values2)
        {
            if (values2  > values )
            {
                temp = *values;
                *values = *values2;
                *values2 = temp;
            }
        
        }
    }    
}

int main (void)
{
    int i;
    int values [16] = { 34, -5, 6, 0, 12, 100, 56, 22, 44, -3, -9, 12, 17, 22, 6, 11};
    int n = 16;
    void sort (int *values, int *n);

    printf ("The Array before undergoing the sorting process:\n");
    for (i = 0; i < n; ++i)
        printf ("%d ", values [i]);

    sort (values,&n);
    printf ("\n\nThe Array after undergoing the sorting process:\n");
    
    for (i = 0; i < n; ++i)
        printf ("%d ", values [i]);

    printf ("\n");

    return 0;

}