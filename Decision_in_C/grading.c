#include <stdio.h>

int main (void)
{
    int Numberofgrades, i, grade, gradesum = 0, failurecount = 0;
    float average;

    printf ("How many grades do you want to enter? ");
    scanf ("%d", &Numberofgrades);

    for (i = 1; i <= Numberofgrades; i++)
    {
        printf ("Enter grade #%d: ", i);
        scanf ("%d", &grade);
        
        gradesum += grade;

        if (grade < 65)
        
            failurecount++;
    }

        average = (float)gradesum / Numberofgrades;

        printf ("\nGrade average = %.2f\n", average);
        printf ("Number of failures = %d\n", failurecount);

        return 0;

}