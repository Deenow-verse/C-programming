#include <stdio.h>

#define IS_UPPER_CASE(x) (((x) >= 'A') && ((x) <= 'Z'))
#define IS_LOWER_CASE(x) (((x) >= 'a') && ((x) <= 'z'))
#define IS_ALPHABETIC(x) ((IS_LOWER_CASE (x)) || (IS_UPPER_CASE (x)))

int main (void)
{
    if (IS_ALPHABETIC ('N'))
    printf ("The provided input is an alphabet\n");
    else
    printf ("The provided input is not an alphabet\n");

    if (IS_ALPHABETIC ('n'))
    printf ("The provided input is an alphabet\n");
    else
    printf ("The provided input is not an alphabet\n");

    if (IS_ALPHABETIC ('1'))
    printf ("The provided input is an alphabet\n");
    else
    printf ("The provided input is not an alphabet\n");

    if (IS_ALPHABETIC ('@'))
    printf ("The provided input is an alphabet\n");
    else
    printf ("The provided input is not an alphabet\n");

    return 0;

}