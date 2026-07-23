#include <stdio.h>

void sort (int *values, int *n);

int main (void)
{
    int i;
    int values [16] = { 34, -5, 6, 0, 12, 100, 56, 22, 44, -3, -9, 12, 17, 22, 6, 11};
    int n = 16;

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

void sort (int *values, int *n)
{
    int *ptr1, *ptr2, temp;
    int *const arrayEnd = values + *n;

    for (ptr1 = values; ptr1 < arrayEnd - 1; ++ptr1)
    {
        for (ptr2 = ptr1 + 1; ptr2 < arrayEnd ; ++ptr2)
        {
            if (*ptr2  > *ptr1 )
            {
                temp = *ptr1;
                *ptr1 = *ptr2;
                *ptr2 = temp;
            }
        
        }
    }    
}