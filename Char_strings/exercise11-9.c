#include <stdio.h>

int main(void)
{
    int strToInt (char string []);
    
    printf ("%i\n", strToInt ("245"));
    printf ("%i\n", strToInt ("100" )+ 25);
    printf ("%i\n", strToInt ("13x5"));
    printf ("%i\n", strToInt ("-245"));

    return 0;

}

int strToInt (char string [])
{
    int i = 0, intValue, result = 0;
    _Bool isnegative = 0;

    if (string [0] == '-')
    {
        isnegative = 1;
        i = 1;
    }   

    while (string [i] >= '0' && string [i] <= '9')
    {        
        intValue = string [i] - '0';
        result = result * 10 + intValue;
        ++i;
    }

    if (isnegative)
    {
        result = -result;
    }

    return result;
}