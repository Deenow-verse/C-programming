#include <stdio.h>

int main (void)
{
     
    char result [81];

    const char string [] = "You know that you should be careful";
    void extractString (const char source [], int start, int count, char result []);

    extractString (string, 18, 30, result);
    printf ("%s\n",result);

    extractString (string, 4, 9, result);
    printf ("%s\n", result);

    extractString (string, 14, 44, result);
    printf ("%s\n", result);

    extractString (string, 44, 50, result);
    printf ("%s\n", result);

    return 0;
}

int count_char (const char string [])
{  
    int i, j = 0;

   while (string [j] != '\0')
   ++j;

   return j;

}

void extractString (const char source [], int start, int count, char result [])
{
    int i, end;
    int count_char (const char string []);

    end = count_char (source);
    
    for (i = 0; i < count; ++i)
    {
        if ((i + start) >= end)
        break;

        result [i] = source [start + i]; 
    }

    result [i] = '\0';
 
}