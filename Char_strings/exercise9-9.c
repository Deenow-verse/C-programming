#include <stdio.h>
#include <stdbool.h>

int main (void)
{
   bool stillFound = true;
   bool replaceAtleastOnce = false;
   char text [50] = "The wrong son";
   char add [] = "per";
   char remove [] = "son";
   bool replaceString (char source [], char s1 [], char s2 []);

   stillFound = replaceString (text, remove, add);
   if (stillFound == false)
   printf ("The string you want to replace '%s' is not in '%s'\n", remove, text);

   else 
  {
    replaceAtleastOnce = true;

    do
    {
        stillFound = replaceString (text, remove, add);
        
    }

    while ( stillFound );
   

    printf ("%s\n", text);
  }
   
   
   

   return 0;

} 

int stringlen (char string [])
{
    int len = 0;
    while (string [len] != '\0')
    {
        ++len;
    }

    return len;
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

void removeString (char source [], int start, int numberOfChar)
{
   int len;
   int stringlen (char string []);
   len = stringlen (source);
        
    while ((start + numberOfChar) <= len)
    {
        source [start] = source [start + numberOfChar];
        ++start;
    }

}

void insertString (char source [], char insert [], int position)
{
    int insertLen = stringlen (insert);
    int sourceLen = stringlen (source);

   while (sourceLen >= position)
   {
        source [(sourceLen + insertLen)] = source [sourceLen] ;
        --sourceLen; 
   }
   
   for (int i = position, j = 0; j < insertLen; ++i, ++j)
   {
    source [i] = insert [j];
   }


}

bool replaceString (char source [], char s1 [], char s2 [])
{
    int start, numberOfChar;

    int stringlen (char string []);
    int findString (const char source [], const char search []);
    void removeString (char source [], int start, int numberOfChar);
    void insertString (char source [], char insert [], int position);

    start = findString (source, s1);
    numberOfChar = stringlen (s1);
    
    if (start == -1)
    return false;    

    else
    {
        removeString (source, start,numberOfChar );
        insertString (source, s2, start);
    }

    return true;

}