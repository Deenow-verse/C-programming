#include <stdio.h>

int main (void)
{
    int i, j;
    int original_matrix [4][5]={ {4, 7, 8, 0, 2}, {4, 5, 10, 15, 11}, {7, 6, 0, 3, 1}, {2, 6, 23, 19, 17} };
    int transposeMatrix (int matrix0 [4][5]);

    for ( i = 0; i < 4; ++i)
    {
        for ( j = 0; j < 5; ++j)
        {
            printf ("%2i ", original_matrix [i][j]); 
        }

    printf ("\n");

    }
    
    printf ("\n\n");

    transposeMatrix (original_matrix);

    return 0;

}

int transposeMatrix (int matrix0 [4][5])
{
    int i, j, matrix1 [5][4];

    for (i = 0; i < 5; ++i)
    {
        for (j = 0; j < 5; ++j)
        {
            matrix1 [i] [j] = matrix0 [j][i];
        }
    }

    
    for ( i = 0; i < 5; ++i)
    {
        for ( j = 0; j < 4; ++j)
        {
            printf ("%2i ", matrix1 [i][j]); 
        }

    printf ("\n");

    }
    printf ("\n\n");

}