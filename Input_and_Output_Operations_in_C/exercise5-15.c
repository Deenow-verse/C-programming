#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    FILE *fp = fopen("file1.txt", "r");
    char *buffer = NULL;
    size_t bufferLen = 0;
    int m, i, n;

    if (fp == NULL)
    {
        fprintf (stderr, "Can't open file1.txt for reading\n");
        exit (EXIT_FAILURE);
    }

    printf ("Enter the starting position you want to start extracting each line\n");
    scanf ("%d", &m);
    printf ("Enter the end position you want to finish the extraction of each line\n");
    scanf ("%d", &n);
    printf ("\n\n");

    while (getline(&buffer, &bufferLen, fp) != -1)
    {
        i = m - 1;

        while ((*(buffer + i ) != '\n') && (*(buffer + i ) != '\0') && i < n)
        {
            fprintf (stdout, "%c",*(buffer + i));
            ++i;
        }

        fprintf (stdout, "\n");
    }

    free(buffer);
    fclose(fp);

    return 0;
}