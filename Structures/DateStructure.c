#include <stdio.h>

int main (void)
{
    struct date 
    {
        int day;
        int month;
        int year;
    };
    
    struct date today;

    today.day == 4;
    today.month == 1;
    today.year == 1448;

    printf ("Todays date is %i / %i / %i", today.day, today.month, today.year % 100);

    return 0;
}