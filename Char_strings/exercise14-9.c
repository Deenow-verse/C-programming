#include <stdio.h>

int main (void) 
{
    char str [20];
    void IntToStr (long long number, char string []);
    
    IntToStr (-4294967295, str);
    printf ("%s\n", str);

    IntToStr (867, str);
    printf ("%s\n", str);

    IntToStr (0, str);
    printf ("%s\n", str);

    return 0;
}

void IntToStr (long long number, char string [])
{
    int i = 0, divisor = 1;
    long long numberCopy = number;
    
    if (number < 0)
    {
        string [0] = '-';
        numberCopy *= -1;
        number *= -1;
        i = 1;
    }

    while (numberCopy > 10)
    {
        numberCopy /= 10;
        divisor *= 10;
    }

    do
    {
        string [i] = number / divisor + '0';
        number %= divisor;
        divisor /= 10;
        i++;
    } while (divisor > 0);

    string [i] = '\0';
}
    