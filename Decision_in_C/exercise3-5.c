#include <stdio.h>

int main (void)
{
    int k, n;
    
    printf ("Enter two integers:\n");
    scanf ("%d  %d", &k,  &n);

    if (n ==0)
        printf ("The result is undefined.\n");
    else
        printf ("The result is %f.\n", (float)k/n);

    return 0;    

}