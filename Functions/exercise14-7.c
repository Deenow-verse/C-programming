#include <stdio.h>

int gconverted_number [64];
long int gnumber_toconvert = 1;
int gbase;
int gdigit;

int main (void)
{
    void getNumberandBase (void), convertNumber (void), displayNumber (void);

    while (1)
    {
    gdigit = 0;

    getNumberandBase ();

    if (gnumber_toconvert == 0)
   {
        printf ("The program has been terminated\n");
        break;
    }

    convertNumber ();
    displayNumber ();
    printf ("\n");
    }

    return 0;
    

}

void getNumberandBase (void)
{
    printf ("Enter the number you want to be converted (if you have converted all the numbers just press 0 to terminate)\n");
    scanf ("%ld", &gnumber_toconvert);   
    
    if (gnumber_toconvert != 0)
    {
        printf ("Enter the base you want to convert to (2 - 16)\n");
        scanf ("%d", &gbase);
    

        while (gbase < 2 || gbase > 16)
        {
            printf ("\n\nInvalid base entered, the base must be between 2 and 16\n");
            printf ("\nPlease now enter a valid base\n");
            scanf ("%d", &gbase);
        }
    }

}    

void convertNumber (void)
{
    do 
    {
        gconverted_number [gdigit] = gnumber_toconvert % gbase;
        gnumber_toconvert /= gbase;
        ++gdigit;
    }
    while (gnumber_toconvert != 0);
    
}

void displayNumber (void)
{
    const char baseDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    int nextdigit;

    printf ("The converted number is: ");
    for (--gdigit; gdigit >= 0; --gdigit)
    {
        nextdigit = gconverted_number [gdigit];
        printf ("%c", baseDigits [nextdigit]);
    }

    printf ("\n");
}