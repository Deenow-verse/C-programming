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

    if (string [0] == '-')
        {
            printf ("-");
            
            while (string [i - 1] != '\0')
            {
                string [i] = string [i + 1];
                ++i;
            }
        }

    for (i = 0;(string [i] >= '0' && string [i] <= '9'); i++)
    {        
        intValue = string [i] - '0';
        result = result * 10 + intValue;
    }

    return result;
}