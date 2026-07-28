#include <stdio.h>

#define MAX3(a, b, c) (((a) > (b) && (a) > (c)) ? (a) : (((b) > (c)) ? (b) : (c) ))

int main (void)
{
    int Maximum_value;

    Maximum_value = MAX3 (5, 7, 12);     
    printf ("The Largest in value of the three numbers is %d\n", Maximum_value);

    Maximum_value = MAX3 (18, 13, 1);     
    printf ("The Largest in value of the three numbers is %d\n", Maximum_value);

    Maximum_value = MAX3 (5, 5, 5);
    printf ("The Largest in value of the three numbers is %d\n", Maximum_value);

    Maximum_value = MAX3 (25, 77, 32);
    printf ("The Largest in value of the three numbers is %d\n", Maximum_value);
}