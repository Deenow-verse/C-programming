#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int start_pos, end_pos;

void getExtractionRange(void);
void extractString (FILE *fp);

int main (void)
{
    FILE *fp = fopen("file1.txt", "r");

    if (fp == NULL)
    {
        fprintf (stderr, "Can't open file1.txt for reading\n");
        exit (EXIT_FAILURE);
    }
    
    getExtractionRange ();
    extractString(fp);
    
    fclose(fp);

    return 0;
}

void getExtractionRange(void)
{
    printf ("Enter the starting position you want to start extracting each line\n");
    scanf ("%d", &start_pos);

    while (start_pos <= 0)
    {
        printf("choose a start greater than 0\n");
        scanf ("%d", &start_pos);
    }

    printf ("Enter the end position you want to finish the extraction of each line\n");
    scanf ("%d", &end_pos);

    while (start_pos > end_pos)
    {
        printf("choose an end position greater than starting position\n");
        scanf ("%d", &end_pos);
    }

    printf ("\n\n");
}

void extractString (FILE *fp)
{
    char *buffer = NULL;
    size_t bufferLen = 0;
    ssize_t charsRead;
    
    while ((charsRead = getline(&buffer, &bufferLen, fp)) != -1) 
    {
        int start_idx = start_pos - 1;
        int length_to_print = end_pos - start_idx; 

        if (start_idx < charsRead) 
        {
            fprintf(stdout, "%.*s", length_to_print, buffer + start_idx);
        }
        
        fprintf(stdout, "\n");
    }

    free(buffer);
    return;
}