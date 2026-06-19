#include <stdio.h>
#include <stdbool.h>

struct date 
{
    int day;
    int month;
    int year;
};

int main (void)
{
    struct date today, tommorrow;
    int numberofdays(struct date d);

    printf ("Enter todays date (dd mm yy)");
    scanf ("%d  %d  %d", &today.day, &today.month, &today.year);

     if (today.day != numberofdays (today))
    {
        tommorrow.day = today.day + 1;
        tommorrow.month = today.month;
        tommorrow.year = today.year;
    }

    else if (today.month == 12)
    {
        tommorrow.day = 1;
        tommorrow.month = 1;
        tommorrow.year = today.year + 1;
    }

    else 
    {
        tommorrow.day = 1;
        tommorrow.month = today.month + 1;
        tommorrow.year = today.year;
    }

    printf ("Tommorows date is %d/ %d/ %.2d.\n", tommorrow.day, tommorrow.month, tommorrow.year % 100);

    return 0;

}

int numberofdays (struct date d)
{
    int days;
    bool isLeapYear (struct date d);
    const int daypermonth [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeapYear (d) == true && d.month == 2)
    days = 29;

    else
    days = daypermonth [d.month - 1];

    return days;  
}

bool isLeapYear (struct date d)
{
   bool leapYearFlag;

   if ((d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0)
   {
    leapYearFlag = true;
   }

   else 
   leapYearFlag = false;

   return leapYearFlag;
}