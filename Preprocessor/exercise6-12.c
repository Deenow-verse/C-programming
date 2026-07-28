#include <stdio.h>

#define IS_UPPER_CASE(x) (((x) >= 'A') && ((x) <= 'Z'))

int main (void)
{
   if ( IS_UPPER_CASE ('Q'))
   printf ("The letter is in uppercase\n");
   else
   printf ("The letter is not in uppercase\n");

   if ( IS_UPPER_CASE ('a'))
   printf ("The letter is in uppercase\n");
   else
   printf ("The letter is not in uppercase\n");

   return 0;

}