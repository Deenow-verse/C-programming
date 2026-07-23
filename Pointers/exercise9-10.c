#include <stdio.h>

void readLine (char *buffer);   

int main (void)
{
    int i;
    char line [81];
    
    for (i = 0; i < 3; ++i)
    {
        readLine (line);
        printf ("\n%s\n\n", line);
    }

    return 0;

}

void readLine (char *buffer)
{
    char character;

    do 
    {
        character = getchar ();
        *buffer++ = character;
    }
    while (character != '\n');

    *--buffer = '\0';
    
}