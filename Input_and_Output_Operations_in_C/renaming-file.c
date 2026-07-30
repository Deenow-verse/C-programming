#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    if ( rename ("tempfile.pdf", "database") ) 
    {
        fprintf (stderr, "Can't rename tempfile\n");
        exit (EXIT_FAILURE);
    }

    return 0;
}