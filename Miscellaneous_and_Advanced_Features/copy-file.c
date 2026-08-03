#include <stdio.h>

int main (int argc, char *argv[])
{
    FILE *in, *out;
    int c, counter = 0;

    if (argc != 3)
    {
        fprintf (stderr, "Need two files names\n");
        return 1;
    }

    if ( (in = fopen (argv[1], "r")) == NULL )
    {
        fprintf (stderr, "Can't read %s.\n", argv[1]);
        return 2;
    }

    if ( (out = fopen (argv[2], "w")) == NULL )
    {
        fprintf (stderr, "Can't write %s.\n", argv[2]);
        return 3;
    }

    while ( (c = getc (in)) != EOF )
    {
        putc (c, out);
        ++counter;
    }

    fclose (in);
    fclose (out);

    printf ("Copied %d characters from %s to %s.\n", counter, argv[1], argv[2]);
    return 0;
}