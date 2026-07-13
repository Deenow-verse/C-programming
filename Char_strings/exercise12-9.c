#include <stdio.h>

int main(void)
{
    float strToFloat (char string []);

    printf ("%f\n", strToFloat ("-867.6921"));

    return 0;

}

float strToFloat (char string [])
{
    int i = 0, intValue;
    float result = 0.0, divisor = 10.0;
    _Bool isNegative = 0, hasDecimal;

    if (string [0] == '-')
    {
        isNegative = 1;
        i = 1;
    }   

    while (string [i] != '\0')
    {  
        if (string [i] == '.')
        hasDecimal = 1;

        else if (string [i] >= '0' && string [i] <= '9')
        {
            if (!hasDecimal)
            {
                result = result * 10.0 + (string [i] - '0');
            }
            else
            {
                result += (string [i] - '0') / divisor;
                divisor *= 10.0;
            }
        }
        ++i;
    }

    return isNegative ? -result : result;
}