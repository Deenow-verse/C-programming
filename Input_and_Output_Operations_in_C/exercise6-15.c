#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void getFileNames (char *file1);
char getFeedback (void);
void printFileSubset (FILE *extractFrom);

int main (void)
{
    char file1Name [64];
    FILE *file1;    

    getFileNames (file1Name);

    if ((file1 = fopen (file1Name, "r")) == NULL)
    {
        fprintf (stderr, "Can't open %s for reading\n", file1Name);
        exit (EXIT_FAILURE);
    }

    printFileSubset (file1);

    fclose (file1);
    
    return 0;
}

void getFileNames (char *file1)
{    
    printf ("Enter the name of the file you want to extract lines from:\n\n");
    scanf ("%s", file1);

    printf ("\n");

    return;
}

char getFeedback (void)
{
    char C;

    printf ("\n\nDo you want to continue?:\n");
    printf ("if so the press the 'q' button else press any character key on your keyboard\n");
    scanf ("%c", &C);
    return C;
}

void printFileSubset (FILE *extractFrom)
{
    int i, n = 20, j = 0;
    char action;
    char *buffer = NULL;
    size_t bufferLen = 0;

   for (i = 1;  i <= n; ++i)
        {           
            while (getline(&buffer, &bufferLen, extractFrom) != -1)
            {         
                if ((*(buffer) == '\n')) 
                break;
                
                else
                fprintf (stdout, "%s", buffer);
            }

            if (i  == n)
            {
                action = getFeedback ();
                
                if (action == 'q')
                {
                    break;
                }

                else
                n += 20;
            }
            
        }

    return;
}