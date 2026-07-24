#include <stdio.h>

struct entry
{
    char word[15];
    char definition[50];
};

int lookup (const struct entry dictionary[], const char search[], const int entries);
int compareStrings (const char s1[], const char s2[]);


int main (void)
{
    const struct entry dictionary[100] =
    { 
        { "aardvark", "a burrowing African mammal"},

        { "abyss","a bottomless pit"},

        { "acumen", "mentally sharp; keen" },

        { "addle", "to become confused" },

        { "aerie", "a high nest" },

        { "affix", "to append; attach" },
        
        { "agar", "a jelly made from seaweed" },

        { "ahoy", "a nautical call of greeting" },

        { "aigrette", "an ornamental cluster of feathers" },
        
        { "ajar","partially opened" }

};

    int entries = 10;
    char word[15];
    int entry;
        
    printf ("Enter word: ");
    scanf ("%14s", word);
    
    entry = lookup (dictionary, word, entries);
    
    if ( entry != -1 )
    printf ("%s\n", dictionary[entry].definition);
    
    else 
    printf ("Sorry, the word %s is not in my dictionary.\n", word);
    
    return 0;
}

int compareStrings (const char *s1, const char *s2)
{
    int answer;

    while ( *s1 == *s2 && *s1 != '\0'&& *s2 != '\0')
    {
        ++s1;
        ++s2;
    }

    if ( *s1 < *s2 )
    answer = -1;

    else if ( *s1 == *s2 )
    answer = 0;

    else
    answer = 1;

    return answer;
}

int lookup (const struct entry dictionary[], const char search[], const int entries)
{
    int low = 0, high = entries - 1, mid, result;
    
    while ( low <= high )
    {
        mid = (low + high) / 2;
        result = compareStrings (dictionary[mid].word, search);

        if ( result == -1 )
            low = mid + 1;
        else if ( result == 1 )
            high = mid - 1;
        else
            return mid;
    }

return -1;

}
