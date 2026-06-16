#include <stdio.h>

int main (void)
{
  int number,sign;

  printf ("PLEASE TYPE IN A NUMBER:");
  scanf ("%i", &number);

  if (number < 0)
       sign = -1;
    
    else if (number == 0)
       sign = 0;
       
    else 
       sign = 1;
       
  printf ("sign = %i\n", sign);
  
  return 0;
  
}