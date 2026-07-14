#include <stdio.h>

int main (void)
{
    void copyString (char *to, const char *from);
    char string1[80];
    char string2[] = "This is a string to be copied.";

    copyString (string1, string2);
    printf ("string1: %s\n", string1);

    copyString (string1, "So is this.");
    printf ("%s\n", string1);

    return 0;
}

void copyString (char *to, const char *from)
{
    for (  ; *from != '\0'; ++from, ++to)
    {
        *to = *from;
    }

    *to = '\0';
}