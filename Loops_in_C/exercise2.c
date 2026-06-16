#include <stdio.h>

int main (void)
{
    int n, triangularNumber;

    printf ("A TABLE OF EVERY FIFTH TRIANGULAR NUMBERS BETWEEN 5 AND 50\n\n");
    printf ("Number                                    Triangular number\n");
    printf ("______                                    __________________\n");

    triangularNumber = 0;
    for (n = 5; n <= 50; n = n + 5){
        triangularNumber = n * (n + 1) / 2; 

    printf ("%2i                                                 %2i\n", n, triangularNumber);  

    }

    return 0;

}