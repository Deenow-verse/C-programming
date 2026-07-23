#include <stdio.h>

int main (void)
{
    int i;
    char line [81];
    void readLine (char *buffer);

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
    int i = 0;

    do 
    {
        character = getchar ();
        *buffer = character;
        ++buffer;
    }
    while (character != '\n');

    *buffer = '\0';
    
}