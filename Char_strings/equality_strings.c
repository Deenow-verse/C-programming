#include <stdio.h>
#include <stdbool.h>

int main (void)
{
    bool equalString (const char s1 [], const char s2 []);
    const char stra [] = "string compare test";
    const char strb [] = "string";

    printf ("%i\n", equalString (stra, strb));
    printf ("%i\n", equalString (stra, stra));
    printf ("%i\n", equalString (strb, "string"));

    return 0;

}

bool equalString (const char s1 [], const char s2 [])
{
    int i = 0; 
    bool areEqual;

    while (s1 [i] == s2 [i] && s1 [i] != '\0' && s2 [i] != '\0')
    ++i;

    if (s1 [i] == '\0' && s2 [i] == '\0')
    areEqual = true;

    else
    areEqual = false;

    return areEqual;
}

