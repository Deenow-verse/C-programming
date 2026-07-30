#include <stdio.h>
#include <stdlib.h>

FILE *openFile (const char *file);

int main (void)
{
    char inName [64];
    FILE *my_file;

    printf ("Enter the name of the file you want to open: ");
    scanf ("%63s", inName);

    my_file = openFile(inName);
    
    printf("Success! The file was opened.\n");

    fclose(my_file);

    return 0;
    
}
FILE *openFile (const char *file)
{
    char inName [64];
    FILE *inFile;

   
    
    if ( (inFile = fopen (inName, "r")) == NULL )
    {
        fprintf (stderr, "Can't open %s for reading.\n", file);
        exit (EXIT_FAILURE);
    }
    
    return inFile;
}