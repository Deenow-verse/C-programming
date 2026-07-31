#include <stdio.h>
#include <stdlib.h>

#define TOUPPER(c) ((c) - ('a') + ('A'))
int main (void)
{
    char copyfrom[64], pasteto [64];
    int c;
    FILE *original, *copyto;


    printf ("Enter the name of the file to be copied: ");
    scanf ("%63s", copyfrom);

    printf ("Enter the name of output file: ");
    scanf ("%63s", pasteto);

    if ((original = fopen (copyfrom, "r")) == NULL)
    {
        fprintf (stderr, "Can't open %s for reading\n", copyfrom);
        exit (EXIT_FAILURE);
    }

    if ((copyto = fopen (pasteto, "w")) == NULL)
    {
        fprintf (stderr,  "Can't open %s for writing\n", pasteto);
        exit (EXIT_FAILURE);
    }
    
    while ((c = getc (original)) != EOF)
    {
        if (c >= 'a' && c <= 'z')
        {
            putc (TOUPPER (c), copyto);
        }

        else
        putc (c, copyto);
    }

    fclose (original);
    fclose (copyto);

    printf ("File has been copied and changed to Uppercase Character where their was Lowercase character successfully\n");

    return 0;    
}