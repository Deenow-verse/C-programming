#include <stdio.h>

int main (void)
{
    void scalarmultiply (int matrix [3][5], int scalar);
    void displaymatrix (int matrix [3][5]);
    int samplematrix [3][5] = { { 7, 16, 55, 13, 12 }, { 12, 10, 52, 0, 7 }, { -2, 1, 2, 4, 9 } };

    printf ("The original matrix is:\n");
    displaymatrix (samplematrix);

    scalarmultiply (samplematrix, 2);
    printf ("\nThe matrix after being multiplied by 2 is:\n");
    displaymatrix (samplematrix);

    printf ("\nThe matrix after being multiplied by -1 is:\n");
    scalarmultiply (samplematrix, -1);
    displaymatrix (samplematrix);

    return 0;

}

void scalarmultiply (int matrix [3][5], int scalar)
{
    int row, column;
    
    for (row = 0; row < 3; ++row)   
    {
        for (column = 0; column < 5; ++column)
        {
            matrix [row][column] *= scalar;
        }
    }
}

void displaymatrix (int matrix [3][5])
{
    int row, column;

    for (row = 0; row < 3; ++row)
    {
        for (column = 0; column < 5; ++column)
        {
            printf ("%4i ", matrix [row][column]);
        }
        printf ("\n");
    }
}
    