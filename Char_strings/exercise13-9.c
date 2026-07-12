#include <stdio.h>

int main (void) 
{
    char upper;
    char uppercase (void);

    upper = uppercase ();

    printf ("The uppercase of the character is %c\n", upper);

    return 0;

}

char getCharacter (void)
{
    char lower;
    printf ("Enter the character you want to be converted to its uppercase:\n");
    scanf ("%c", &lower);

    return lower;
} 

char uppercase (void)
{
    char lower, upper;
    char getCharacter (void);

    lower = getCharacter ();

    upper = lower - ('a' + 'A');   

    return upper;

}