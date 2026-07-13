#include <stdio.h>

char string [81];

int main (void) 
{
    char uppercase (void);

    uppercase ();

    printf ("The uppercase of the character is %s\n", string);

    return 0;

}

char getString (void)
{
    printf ("Enter the words you want its lowercase characters to be converted to  uppercase:\n");
    scanf ("%80[^\n]s", string);
} 

char uppercase (void)
{
    int i = 0;
    char getString (void);

    getString ();

    while (string [i] != '\0')
    {
        if (string [i] >= 'a' && string [i] <= 'z' )
        {
            string [i] = string [i] - 'a' + 'A';
        }
        ++i;
    }      

}