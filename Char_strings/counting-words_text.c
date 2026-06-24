#include <stdio.h>
#include <stdbool.h>

int main (void)
{
    char text [81];
    int totalWords = 0;
    int countWords (const char string []);
    void readLine (char buffer []);
    bool endOfText = false;

    printf ("Enter your text\n");
    printf ("When you are done press return\n\n");

    while (! endOfText)
    {
        readLine (text);

        if ( text [0] == '\0')
        {
            endOfText = true;
        }

        else 
        totalWords += countWords (text);
    }

    printf ("\nTheir are %i words in the above text.\n", totalWords);
    
    return 0;
    
}

bool alphabetic (const char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    return true;

    else 
    return false;

}

void readLine (char buffer [])
{
    char character;
    int i = 0;

    do 
    {
        character = getchar ();
        buffer [i] = character;
        ++i;
    }
    while (character != '\n');

    buffer [i-1] = '\0';
    
}

int countWords (const char string [])
{
    int i, wordcount = 0;
    bool lookingForward = true , alphabetic (const char c);

    for (i = 0; string [i] != '\0'; ++i)
    {
        if (alphabetic (string [i]) )
        {
            if (lookingForward)
            {
                ++wordcount;
                lookingForward = false;
            }
        }

       else 
       lookingForward = true;
    }

    return wordcount;
}