#include <stdio.h>

int main (void)
{
    int ratingcounters [10], i, response;

    for (i = 1; i <= 10; ++i)
    {
        ratingcounters [i] = 0;
    }

    printf ("Enter your responses\n");

    for (i = 1; i <= 20; ++i)
    {
        scanf ("%d", &response);

        if (response < 1 || response >10)
        printf ("Bad response: %d", response);

        else 
        ++ratingcounters [response];
    }

    printf ("\n\nRatings      Number of response\n");
    printf ("------------    --------------------\n");

    for (i = 1; i <= 10; ++i)
        printf ("%4i%14i\n", i, ratingcounters [i]);

return 0;        

}