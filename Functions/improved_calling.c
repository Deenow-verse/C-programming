# include <stdio.h>

void printmessage (void)
{
    printf ("Hello, World!\n");
}

int main (void)
{
    for (int i = 1; i <= 5; ++i)
    printmessage ();
    
    return 0;
}