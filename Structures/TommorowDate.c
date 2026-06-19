#include <stdio.h>

int main (void)
{
    struct date 
    {
        int day;
        int month;
        int year;
    };
    
    struct date today, tommorow;

    const int dayspermonth [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf ("Enter todays date (dd mm yy)");
    scanf ("%d  %d  %d", &today.day, &today.month, &today.year);

    if (today.day != dayspermonth [today.month - 1])
    {
        tommorow.day = today.day + 1;
        tommorow.month = today.month;
        tommorow.year = today.year;
    }

    else if (today.month == 12)
    {
        tommorow.day = 1;
        tommorow.month = 1;
        tommorow.year = today.year + 1;
    }

    else 
    {
        tommorow.day = 1;
        tommorow.month = today.month + 1;
        tommorow.year = today.year;
    }

    printf ("Tommorows date is %d/ %d/ %.2d.\n", tommorow.day, tommorow.month, tommorow.year % 100);

    return 0;
}