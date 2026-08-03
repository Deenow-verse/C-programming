#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

struct entry 
{
    char word [15];
    char definition [50];
};

bool equalString (const char str1[], const char str2 []);
int lookup (const struct entry dictionary [], const char search[], const int entries);

int main (int argc, char *argv[])
{
    const struct entry dictionary[100] =
    { 
        { "aardvark", "a burrowing African mammal" },
        
        { "abyss", "a bottomless pit" },
        
        { "acumen", "mentally sharp; keen" },
        
        { "addle", "to become confused" },
        
        { "aerie", "a high nest" },
        
        { "affix", "to append; attach" },
        
        { "agar", "a jelly made from seaweed" },
        
        { "ahoy", "a nautical call of greeting" },
        
        { "aigrette", "an ornamental cluster of feathers" },
        
        { "ajar", "partially opened"},
    };
    
    int entries = 10;
    int entryNumber;
       
    if ( argc != 2 )
    {
        fprintf (stderr, "No word typed on the command line.\n");
        
        return EXIT_FAILURE;
    }
    
    entryNumber = lookup (dictionary, argv[1], entries);
    
    if ( entryNumber != -1 )
    printf ("%s\n", dictionary[entryNumber].definition);
    
    else
    printf ("Sorry, %s is not in my dictionary.\n", argv[1]);
    
    return EXIT_SUCCESS;
}

bool equalString (const char str1[], const char str2 [])
{
    int i = 0;
    bool areEqual;

    while (str1[i] == str2 [i] && str1 [i] != '\0' && str2 [i] != '\0')
    ++i;

    if (str1 [i] == '\0' && str2 [i] == '\0')
    areEqual = true;

    else 
    areEqual = false;

    return areEqual;
}

int lookup (const struct entry dictionary [], const char search [], const int entries)
{
    int i;
    bool equalString (const char str1[], const char str2 []);

    for (i = 0; i < entries; ++i)
    if (equalString (search, dictionary [i].word))
    return i;

    return  -1;
    
}