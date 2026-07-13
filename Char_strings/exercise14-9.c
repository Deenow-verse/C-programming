#include <stdio.h>

int main (void) 
{
    char str [20];
    char IntToStr (int number, char string []);
    
    IntToStr (-867, str);
    printf ("%s\n", str);

    IntToStr (867, str);
    printf ("%s\n", str);

    return 0;
}

char IntToStr (int number, char string [])
{
    int i = 0, divisor = 1;
    
    if (number < 0)
    {
        string [0] = '-';
        number *= -1;
        i = 1;
    }

    while (number > 10)
    {
        number /= 10;
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
    