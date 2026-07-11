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

bool alphanumeric (const char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
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
    bool lookingForward = true , alphanumeric (const char c);

    for (i = 0; string [i] != '\0'; ++i)
    {
        if (alphanumeric (string [i]) )
        {
            if (lookingForward)
            {
                ++wordcount;
                lookingForward = false;
            }
        }

       else if ((string [i] == '\'' && i > 0 && alphanumeric (string [i - 1]) && alphanumeric (string [i + 1])) || (string [i] == '-' && (string [i + 1] >= '0' || string [i + 1] <= '9')))
        lookingForward = false; 

       else 
       lookingForward = true;
    }

    return wordcount;
}