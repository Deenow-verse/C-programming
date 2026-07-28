#include <stdio.h>

#define ABSOLUTE_VALUE(x) (((x) < 0 ? -(x) : (x)))

int main (void)
{
    int test1 = -192 - 12;
    int test2 = 10;
    int test3 = -9 + test1;

    printf ("The absolute value of test1 %d is %d \n", test1, ABSOLUTE_VALUE (test1));
    printf ("The absolute value of test2 %d is %d \n", test2, ABSOLUTE_VALUE (test2));
    printf ("The absolute value of test3 %d is %d \n", test3, ABSOLUTE_VALUE (test3));
    printf ("The absolute value of test3 + test1 %d is %d \n", test3 + test1, ABSOLUTE_VALUE (test3 + test1));

    return 0;
}