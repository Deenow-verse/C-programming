#include <stdio.h>

int main (void)
{
   char text [50] = "The wrong son";
   char add [] = "per";
   void insertString(char source [], char insert [], int position);

   insertString (text, add , 10);

   printf ("%s\n", text);

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

void insertString (char source [], char insert [], int position)
{
    //shift the char present from source [position] by lenght of insert, start from null the last index and coming back one step till you hit position
    int insertLen = stringlen (insert);
    int sourceLen = stringlen (source);

   while (sourceLen >= position)
   {
        source [(sourceLen + insertLen)] = source [sourceLen] ;
        --sourceLen; 
   }

   //after moving you now write the values of insert in that space left from position to position + insertLen - 1
   
   for (int i = position, j = 0; j < insertLen; ++i, ++j)
   {
    source [i] = insert [j];
   }


}