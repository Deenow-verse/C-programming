#include <stdio.h>

int main (void)
{
   char text [] = "The wrong son";
   void removeString (char source [], int start, int numberOfChar);

   removeString (text, 4, 6);

   printf ("%s\n", text);

   return 0;
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

int stringlen (char string [])
{
    int len = 0;
    while (string [len] != '\0')
    {
        ++len;
    }

    return len;
}