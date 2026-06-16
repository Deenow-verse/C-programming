#include <stdio.h>

int main (void)
{
    float value1, value2;
    char operator;

    printf ("TYPE IN YOUR EXPRESSION:\n");
    scanf ("%f %c %f", &value1, &operator, &value2);

    switch (operator)
    {

    case '+': 
        printf ("%.2f\n", value1 + value2 );
        break;
      
    case '-': 
        printf ("%.2f\n", value1 - value2);
        break;
        
    case  '*' :
    case 'x':
        printf ("%.2f\n", value1 * value2);
        break;

    case '/' :
        if ( value2 == 0 )
           printf ("Division by zero is not allowed\n");
        else  
           printf ("%.2f\n", value1 / value2 );
        break;

    default :
        printf ("Unexpected operator type either ' + - * / ' \n"); 
        break;
    }   
        
    return 0;     
}