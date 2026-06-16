#include <stdio.h>

int main (void)
{
    float a, accumulator;
    char b;

    printf ("The only operators allowed are + (additition), - (subtraction), * (multiplication), / (divide), S (set accumulator) and E to exit.\n");
    
    while (b != 'E')
    {    
        printf ("Enter a number and a valid operator:\n");    
        scanf ("%f %c", &a, &b);

        switch (b)
        {
            case 'S':
                accumulator = a;
                printf ("The content of the accumulator is %f\n", accumulator);
                break;

            case '+':
                accumulator += a; 
                printf ("Result: %f\n", accumulator);
                break;

            case '-':  
                accumulator -= a; 
                printf ("Result: %f\n", accumulator);
                break;

            case '*': 
                accumulator *= a;
                printf ("Result: %f\n", accumulator);
                break;
                
            case '/':
                if (a != 0)
                  {
                   accumulator /= a; 
                   printf ("Result: %f\n", accumulator);
                  }
                else
                  {
                   printf ("Error: Division by zero is not allowed.\n");
                  }
                   break;

            case 'E':
                printf ("Exiting the program.\n");
                printf ("The content of the acummulator is = %f\n", accumulator);
                printf ("End of calculation\n");
                break;
                
            default:  
               printf ("Invalid operator. Please try again.\n"); 
               break;


        }
    }

    return 0;
}