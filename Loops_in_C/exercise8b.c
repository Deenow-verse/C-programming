#include <stdio.h>
int main (void)
{
int n = 1, triangularNumber = 0;

printf ("TABLE OF TRIANGULAR NUMBERS\n\n");
printf (" n                    Sum from 1 to n\n");
printf ("---                   ---------------\n");

while ( n <= 10) 
{

triangularNumber += n;
printf (" %2i                         %i\n", n, triangularNumber);
++n;

}

return 0;

}