#include <stdio.h>
#include <stdbool.h>

int main (void)
{
    int i;
    int array [16] = { 34, -5, 6, 0, 12, 100, 56, 22, 44, -3, -9, 12, 17, 22, 6, 11};
    void sort (int values [], int n, bool a);

    printf ("The Array before undergoing the sorting process:\n");
    for (i = 0; i < 16; ++i)
        printf ("%d ", array [i]);

    sort (array, 16, 0);
    printf ("\n\nThe Array after sorting decending process:\n");
    
    for (i = 0; i < 16; ++i)
        printf ("%d ", array [i]);

    printf ("\n");

    sort (array, 16, 1);
    printf ("\n\nThe Array after sorting in acending order process:\n");
    
    for (i = 0; i < 16; ++i)
        printf ("%d ", array [i]);

    printf ("\n");

    return 0;

}

void sort (int values [], int n, bool a)
{
    int i, j, temp;

    if (a == 1)
    {
        for (i = 0; i < n - 1; ++i)
        {
            for (j = i + 1; j < n; ++j)
            {
                if (values [i] > values [j])
                {
                   temp = values [i];
                   values [i] = values [j];
                   values [j] = temp;
                }
            }
        }
    }

    else
    {
        for (i = 0; i < n - 1; ++i)
        {
            for (j = i + 1; j < n; ++j)
            {
                if (values [i] < values [j])
                {
                   temp = values [i];
                   values [i] = values [j];
                   values [j] = temp;
                }
            }
        }
    }
    
}
