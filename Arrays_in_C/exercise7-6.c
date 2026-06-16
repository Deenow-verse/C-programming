#include <stdio.h>

int main (void)
{
    int p [151], i, j;

    for (i = 0; i < 151; ++i)
    {
        p [i] = 0;
    }    

    for (i = 2; i < 151; ++i)
    {
        if (p [i] == 0)
        {
           for (j = 2; j <= 150; ++j)
           {
               if (i * j < 151)
               {
                  p [i * j] = 1;            
               }
               
            }
                  
        }
   
        
    }


     for (i = 2; i < 151; ++i)
     {    
         if (p [i] == 0)
         {
            printf ("%i ", i);
         }
  }
    
    printf ("\n");
    return 0;

}