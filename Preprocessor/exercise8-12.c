#include <stdio.h>

#define IS_UPPER_CASE(x) (((x) >= 'A') && ((x) <= 'Z'))
#define IS_LOWER_CASE(x) (((x) >= 'a') &&((x) <= 'z'))
#define IS_ALPHABETIC(x) ((IS_LOWER_CASE (x)) || (IS_UPPER_CASE (x)))
#define IS_DIGIT(x)      ((x) >= '0' & (x) <= '9')
#define IS_SPECIAL(x) (!((IS_ALPHABETIC (x)) || (IS_DIGIT (x))))

int main (void)
{
    if (IS_SPECIAL ('@'))
    printf ("This is a special character\n");
    else
    printf ("This is not a special character\n");

    if (IS_SPECIAL ('&'))
    printf ("This is a special character\n");
    else
    printf ("This is not a special character\n");

    if (IS_SPECIAL ('~'))
    printf ("This is a special character\n");
    else
    printf ("This is not a special character\n");
    
    if (IS_SPECIAL ('+'))
    printf ("This is a special character\n");
    else
    printf ("This is not a special character\n");

    if (IS_SPECIAL ('A'))
    printf ("This is a special character\n");
    else
    printf ("This is not a special character\n");

    if (IS_SPECIAL ('p'))
    printf ("This is a special character\n");
    else
    printf ("This is not a special character\n");

    if (IS_SPECIAL ('1'))
    printf ("This is a special character\n");
    else
    printf ("This is not a special character\n");

    return 0;
}
