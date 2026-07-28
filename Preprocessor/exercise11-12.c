#include <stdio.h>
#include <ctype.h>

int main (void)
{
    if (isupper ('c'))
    printf ("The character inputed is an uppercase letter\n");
    else 
    printf ("The character provided is not an uppercase letter\n");

    if (isupper ('A'))
    printf ("The character inputed is an uppercase letter\n");
    else 
    printf ("The character provided is not an uppercase letter\n");

    if (isupper ('@'))
    printf ("The character inputed is an uppercase letter\n");
    else 
    printf ("The character provided is not an uppercase letter\n");

    if (islower ('A'))
    printf ("The character inputed is a lowercase letter\n");
    else 
    printf ("The character provided is not a lowercase letter\n");

    if (islower ('t'))
    printf ("The character inputed is a lowercase letter\n");
    else 
    printf ("The character provided is not a lowercase letter\n");

    if (islower ('9'))
    printf ("The character inputed is a lowercase letter\n");
    else 
    printf ("The character provided is not a lowercase letter\n");

    if (isdigit ('A'))
    printf ("The character inputed is a digit\n");
    else 
    printf ("The character provided is not a digit\n");

    if (isdigit ('2'))
    printf ("The character inputed is a digit\n");
    else
    printf ("The character provided is not an digit\n");

    if (isdigit ('#'))
    printf ("The character inputed is a digit\n");
    else 
    printf ("The character provided is not a digit\n");

    if (!(isdigit ('#') || isupper ('#')  || islower ('#')))
    printf ("The character inputed is a special character\n");
    else 
    printf ("The character provided is not a special character\n");

    return 0;

}