#include <stdio.h>

int main (void)
{
 int F = 27;
 float C;
 
 C = (F - 32) / 1.8;
 printf ("Converting %i F to degree is %f\n", F, C);
}