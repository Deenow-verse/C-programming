#include <stdio.h>

int main (void)
{
    float f = 1.00;
    short int i = 100;
    long int l = 500L;
    double d = 15.00;

    printf ("The resul is a float %g\n", f + i);
    printf ("The resul is a double %f\n", l / d);
    printf ("The resul is a float %f\n", i / l + f);
    printf ("The resul is a long int %ld\n", l * i);
    printf ("The resul is a float %f\n", f / 2);
    printf ("The resul is a is a double %f\n", i / (d + f));
    printf ("The resul is a is a float %f\n", l / (i * 2.0));
    printf ("The resul is a double%f\n", l + i / (double) l);

    return 0;

}