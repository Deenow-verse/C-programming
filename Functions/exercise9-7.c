#include <stdio.h>

int g_x;

int main (void)
{
    int y;
    int getNumber (void);
    int test_if_prime (int y);

    getNumber ();

    printf ("\n%i\n",test_if_prime (y) );

    return 0;
}

int getNumber (void)
{
    int x;
    printf ("Enter the number you want to test as prime:\n");
    scanf ("%d", &g_x);
    return g_x;
} 

int test_if_prime (int y)
{
    int i, rem, result;

   /* printf ("Enter the number you want to test as prime:\n");
    scanf ("%d", &y); */
    
    for (i = 3; i < g_x; i += 2)
    {
        rem = g_x % i;
        
        if (rem == 0)
        {
            result = 1;
            return result;
        }

    }
            
    if (y == 2 || rem != 0)
    {
        result = 0;
        return result;
    }

}