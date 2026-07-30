#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    if ( remove ("tempfile") )
    {
        fprintf (stderr, "Can't remove tempfile\n");
        exit (EXIT_FAILURE);
    }
    
    return 0;
}