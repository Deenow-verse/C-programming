#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* skip_sync_noise (char *stream);

int main (void)
{
    char stream[] = "~~~~~~~~~~PAYLOAD_START";
        
    printf ("The clean stream is: %s \n",skip_sync_noise (stream) );

    return (EXIT_SUCCESS);
}

char* skip_sync_noise (char *stream)
{    
    for (; *stream == '~'; ++stream)
    ;  

    return stream;
}
