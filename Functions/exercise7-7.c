#include <stdio.h>

float g_a, g_b, g_c;

int main (void)
{
    void Solve_quadratic_equation (void);
    float squareroot (float number);
    void getCoefficients (void);

    Solve_quadratic_equation ();

    return 0;
}

void getCoefficients (void)
{
    printf ("Enter the coefficients of your quadratic equations:\n");
    scanf ("%f  %f  %f", &g_a, &g_b, &g_c);
}

float squareroot (float number)
{
    double guess = 1.0;

    while (((guess * guess) / (number)) != 1)
    guess = (number / guess + guess) / 2;
         

    return guess;

}

void Solve_quadratic_equation (void)
{
    float x [2];

    if ( ( g_b * g_b - 4 * g_a * g_c ) < 0 )
    {
        printf ("The roots are imaginary\n");
    }

    x [0] = ( -g_b + squareroot( g_b * g_b - 4 * g_a * g_c ) ) / (2 * g_a);
    x [1] = ( -g_b - squareroot( g_b * g_b - 4 * g_a * g_c ) ) / (2 * g_a);

    printf ("The roots of the equation are %f and %f\n", x [0], x [1]);

}
