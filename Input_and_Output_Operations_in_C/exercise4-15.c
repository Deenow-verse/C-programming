#include <stdio.h>
#include <stdlib.h>

void getFileNames (char *file1 , char *file2 );
void mergeFiles (FILE *file1, FILE *file2);

int main (void)
{
    char file1Name [64], file2Name [64];
    FILE *file1, *file2;    

    getFileNames (file1Name, file2Name);

    if ((file1 = fopen (file1Name, "r")) == NULL)
    {
        fprintf (stderr, "Can't open %s for reading\n", file1Name);
        exit (EXIT_FAILURE);
    }

    if ((file2 = fopen (file2Name, "r")) == NULL)
    {
        fprintf (stderr,  "Can't open %s for reading\n", file2Name);
        exit (EXIT_FAILURE);
    }

   
    mergeFiles (file1, file2);

    fclose (file1);
    fclose (file2);

    return 0;

}

void getFileNames (char *file1 , char *file2 )
{    
    printf ("Enter the name of the 2 files you want merged:\n\n");

    printf ("Enter the name of the first file:\n");
    scanf ("%s", file1);

    printf ("Enter the name of the second file:\n");
    scanf ("%s", file2);

    printf ("\n");

    return;
}

void mergeFiles (FILE *file1, FILE *file2)
{
    int char1, char2;
    int file1_alive = 1; 
    int file2_alive = 1; 

    while (1)
    {  
        if (file1_alive)
        {
            while ((char1 = getc (file1)) != '\n')
            {
                if (char1 == EOF)
                {
                    file1_alive = 0;
                    break;
                }
                
                fprintf (stdout, "%c", char1);
           
            }
        fprintf (stdout, "\n");
        }
        
        if (file2_alive)
        {
            while (((char2 = getc (file2)) != '\n')) 
            {
                if (char2 == EOF)
                {
                    file2_alive = 0;
                    break;
                }

                fprintf (stdout, "%c", char2);           
            }
            
            fprintf (stdout, "\n");
        }

        if (file1_alive == 0 && file2_alive == 0)
        break;
        
    }

    return;
}

/*while ((char1 = getc (file1)) != '\n')
            {
                fprintf (stdout, "%c", char1); 
            }*/

            /* while (((char2 = getc (file2)) != '\n'))
            {
                fprintf (stdout, "%c", char2);
            }*/