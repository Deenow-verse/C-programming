#include <stdio.h>

int main (void)
{
    int stringLength (char *string);
    
    printf ("%i ", stringLength ("stringLength test"));
    printf ("%i ", stringLength (""));
    printf ("%i\n", stringLength ("complete"));

    return 0;
}

int stringLength (char *string)
{
    const char *cptr = string;

    while (*cptr != '\0')
    {
        ++cptr;
    }

    return cptr - string;

}