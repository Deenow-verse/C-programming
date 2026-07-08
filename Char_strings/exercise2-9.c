#include <stdio.h>
#include <stdbool.h>

int main (void)
{
    const char text1 [] = "Well, here goes.";
    const char text2 [] = "And here we go... again.";
    const char text3 [] = "a word containing an apostrophe is the swahili word 'Ng'ombe'.";
    const char text4 [] = "The value to test with negative number is -263775.";
    const char text5 [] = "Lets test for positive numbers 678765.";

    int countWords (const char string []);

    printf ("%s - words = %i\n", text1, countWords (text1) );
    printf ("%s - words = %i\n", text2, countWords (text2) );
    printf ("%s - words = %i\n", text3, countWords (text3) );
    printf ("%s - words = %i\n", text4, countWords (text4) );
    printf ("%s - words = %i\n", text5, countWords (text5) );
        
    return 0;
    
}

bool alphanumeric (const char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
    return true;

    else
    return false;
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