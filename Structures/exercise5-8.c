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
    struct date updatedate (struct date today);
    struct date thisday, nextday;

    printf ("Enter todays date (dd mm yy)\n");
    scanf ("%d  %d  %d", &thisday.day, &thisday.month, &thisday.year);

    nextday = updatedate (thisday);

    printf ("Tommorows date is %d/ %d/ %.2d.\n", nextday.day, nextday.month, nextday.year);

    return 0;

}

struct date updatedate (struct date today)
{
    struct date tommorrow;
    int numberofdays(struct date d);   

    if (today.day != numberofdays (today))
    {
        tommorrow = (struct date)  {today.day + 1 , today.month, today.year};
    }

    else if (today.month == 12)
    {
        tommorrow = (struct date) { 1, 1, today.year + 1};
    }

    else 
    {
        tommorrow =(struct date) { 1, today.month + 1, today.year};
    }

    return tommorrow;

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
