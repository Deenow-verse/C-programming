#include <stdio.h>

int minimum (int values [10])
{
    int minvalue, i;

    minvalue = values [0];
    
    for (i = 1; i < 10; ++i)
    {
        if (values [i] < minvalue)
        minvalue = values [i];
    }

    return minvalue;

}

int main (void)
{
    int scores [10], i , minscore;
    int minimum (int values [10]);

    printf ("Enter ten scores:\n");

    for (i = 0; i < 10; ++i)
    {        scanf ("%d", &scores [i]);}
    
    minscore = minimum (scores);
    
    printf ("\nMinimum score is %d\n", minscore);
    

    return 0;
    
}