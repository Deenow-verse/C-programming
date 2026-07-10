#include <stdio.h>

int main (void)
{
    int test1, test2, test3, test4;
    int findString (const char source [], const char search []);

    test1 = findString ("a character", "act");
    test2 = findString ("a chatterbox", "hat");
    test3 = findString ("a camera man you know", "What");
    test4 = findString ("ababcc", "abc");

    if (test1 == -1)
    printf ("The string is not in the source string.\n");

    else
    printf ("The string is been found to start at position %d of the source string\n", test1);

    if (test2 == -1)
    printf ("The string is not in the source string.\n");

    else
    printf ("The string is been found to start at position %d of the source string\n", test2);

    if (test3 == -1)
    printf ("The string is not in the source string.\n");

    else
    printf ("The string is been found to start at position %d of the source string\n", test3);

    if (test4 == -1)
    printf ("The string is not in the source string.\n");

    else
    printf ("The string is been found to start at position %d of the source string\n", test4);

    return 0;
    
}

int findString (const char source [], const char search [])
{
    int i = 0, j = 0, start ;

    while (search [j] != '\0')
    {
        if (source [i] == search [j] )
        {
            ++j;
            ++i;
        }

        else
        {            
            i = i -j + 1;
            j = 0;
        }

        if (source [i] == '\0' && search [j] != '\0')
        {
            return -1;
        }
                
    }

    start = i -j;

    return start;

}