#include <stdio.h>

struct entry
{
    char word [72];
    char definition [100];
};

int main (void)
{
    void dictionarySort (int n, struct entry dictionary []);

    struct entry dictionary [27] =
    {
    {"apple", "A round fruit with red, green, or yellow skin."},
    {"Banana", "A long curved yellow fruit."},
    {"cherry", "A small round red fruit with a pit."},
    {"date", "A sweet fruit from the date palm tree."},    
    {"Zebra", "A striped African mammal."},
    {"apple", "Duplicate key test - should not exist in real dicts."},
    {"Alpha", "The first letter of the Greek alphabet."},
    {"123", "A number often used in testing."},
    {"42answer", "Reference to Hitchhiker's Guide."},
    {"a1pha", "Mixed alphanumeric starting with letter."},    
    {"apple's", "Possessive form of apple."},
    {"well-known", "Famous or widely recognized."},
    {"naïve", "Lacking experience (with diacritic)."},
    {"@symbol", "A word starting with symbol."},
    {"#hashtag", "Social media term."},    
    {"empty", ""},
    {"short", "Brief."},    
    {"supercalifragilisticexpialidocious", "A nonsense word from Mary Poppins meaning extraordinarily good."},    
    {"café", "A coffee shop or restaurant."},
    {"résumé", "A document summarizing one's qualifications."},    
    {"zoo", "A place where animals are kept for exhibition."},
    {"xylophone", "A musical instrument with wooden bars."},
    {"yellow", "The color between green and orange."},    
    {"", "Empty word key (if your function allows)."},
    {"a", "The first letter of the English alphabet."},
    {"Aardvark", "A nocturnal mammal with a long snout."},
    {"ant", "A small social insect."}

    };

    dictionarySort (27, dictionary);

    for (int i = 0; i <= 26; ++i)
    {
        printf ("%s : %s\n", dictionary[i].word, dictionary[i].definition);
    }
}

char toLower (char c)
{
    if (c >= 'A' && c <= 'Z')
    return c + 32;

    return c;
}

int compareStrings (char s1[], char s2[])
{
    int i = 0, answer;

    while ( toLower (s1[i]) == toLower (s2[i]) && s1[i] != '\0'&& s2[i] != '\0')
    ++i;

    if ( toLower (s1[i]) < toLower (s2[i]) )
    answer = -1;

    else if ( toLower (s1[i]) == toLower (s2[i]) )
    answer = 0;

    else
    answer = 1;

    return answer;
}

void dictionarySort (int n, struct entry dictionary [])
{
    int i, j;
    struct entry temp;
    int compareStrings ( char s1[], char s2[]);

    for (i = 0; i < n - 1; ++i)
    {
        for (j = i + 1; j < n; ++j)
        {
            if (compareStrings (dictionary[i].word , dictionary[j].word )  == 1)
            {
                temp = dictionary [i];
                dictionary [i] = dictionary [j];
                dictionary [j] = temp;
            }

        }
    }
}