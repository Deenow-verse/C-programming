#include <stdio.h>
#include <stdbool.h>

int main (void)
{
    long long  number, divisor = 1, extract, test;
    bool is_negative = false;
   

    printf ("THIS PROGRAM DISPLAYS THE DIGITS OF THE NUMBER YOU ENTER IN ENGLISH\n\n");
    printf ("Enter the number to be displayed \n");
    scanf ("%lld", &number);
   
    if ( number < 0 )
        {
            number *= -1;
            is_negative = true;
            printf ("negative ");
        }
        
    if (number == 0)
    {
        printf ("zero");
    } 
    

    test = number;    
    while (test > 9)
        {
            test /= 10;
            divisor *= 10;
        }    

    while ( divisor >  0)
    {

        extract = number / divisor;            
               
         if (extract == 0)
            printf ("zero ");
            
            else if (extract == 1)
            printf ("one ");
            
            else if (extract == 2)
            printf ("two ");
            
            else if (extract == 3)
            printf ("three ");
            
            else if (extract == 4)
            printf ("four ");
            
            else if (extract == 5)
            printf ("five ");            

            else if (extract == 6)
            printf ("six ");            
        
            else if (extract == 7)
            printf ("seven ");
           
            else if (extract ==8)
            printf ("eight ");
            
            else 
            printf ("nine "); 
            
        number %= divisor; 
        divisor /= 10;         
        


    }

    
    printf ("\n");

    return 0; 
    
}

