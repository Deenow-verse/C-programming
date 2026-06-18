#include <stdio.h>

int g_u, g_v, g_lcm;

int main (void)
{
    int data [2] = {15, 10};

    void getCoefficients (void);
    int calculateGreatestCommonDivisor (int u, int v);
    void calculateLeastCommonDivisor (int u,int v);

    getCoefficients ();
    calculateLeastCommonDivisor (15, 10);

     printf ("The lcm of %i and %i is %i\n", g_u, g_v,g_lcm);

    return 0;

}

void getNumbers (void)
{
    printf ("Enter the two number you want to find LCM of:\n");
    scanf ("%d  %d", &g_u, &g_v);
} 

void calculateLeastCommonDivisor (int u, int v)
{   
    if (u < 0 && v < 0)
   {
    printf ("Enter numbers greater than zero");
   }

   g_lcm = ( u * v ) /  calculateGreatestCommonDivisor (u, v);
  
   return g_lcm;
   
}

int calculateGreatestCommonDivisor ( int u, int v )
{
    int temp;

    while ( v != 0)
    {
        temp = u % v;
        u = v;
        v = temp;
    }

    return u;
    
}