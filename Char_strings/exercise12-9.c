#include <stdio.h>

int main(void)
{
    float strToFloat (char string []);

    printf ("%f\n", strToFloat ("-867.6921"));

    return 0;

}

float strToFloat (char string [])
{
    int i = 0, intValue, result = 0;
    _Bool isnegative = 0;

    if (string [0] == '-')
    {
        isnegative = 1;
        i = 1;
    }   

    while ((string [i] >= '0' && string [i] <= '9') || string [i] == '.')
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