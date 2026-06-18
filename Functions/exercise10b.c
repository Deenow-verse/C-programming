#include <stdio.h>

#define MAX 50

int nrow, ncol;
int original_matrix [MAX][MAX];
int transposematrix [MAX][MAX]; 


void getMatrix (void);
void transposeMatrix (void);
void displaymatrix (void);


int main (void)
{
    getMatrix ();
    transposeMatrix ();
    displaymatrix ();

    return 0;

}

void getMatrix (void)
{
    int i, j;

    printf ("Enter the number of row and column for your matrix \n");
    scanf ("%d   %d", &nrow, &ncol);

    if (nrow > MAX || ncol > MAX || nrow < 0 || ncol < 0)
    {
        printf ("Error! Matrix size must be between 1 and %d", MAX);
    }

    printf ("Enter now the elements of your matrix\n\n ");

     for ( i = 0; i < nrow; ++i)
    {
        for ( j = 0; j < ncol; ++j)
        {
            printf ("Enter the element in row [%d] and coloum [%d]:\n", i, j);
            scanf ("%d", &original_matrix [i][j]); 
        }
   
    }
    
}

void transposeMatrix (void)
{
    int i, j; 

    for (i = 0; i < ncol; ++i)
    {
        for (j = 0; j < nrow; ++j)
        {
            transposematrix [i][j] = original_matrix [j][i];
        }
    }

}

void displaymatrix (void)
{
    int i, j;

    printf ("The transpose matrix of\n\n");

     for ( i = 0; i < nrow; ++i)
    {
        for ( j = 0; j < ncol; ++j)
        {
            printf ("%4i ", original_matrix[i][j]); 
        }

    printf ("\n");

    }

    printf ("is:\n\n");

    for ( i = 0; i < ncol; ++i)
    {
        for ( j = 0; j < nrow; ++j)
        {
            printf ("%4i ", transposematrix[i][j]); 
        }

    printf ("\n");

    }
    printf ("\n\n");

}