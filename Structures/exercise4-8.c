#include <stdio.h>
#include <stdbool.h>

struct time 
{
    int hour;
    int minute;
    int second;
};

struct date 
{
    int day;
    int month;
    int year;
};

struct dateandTime
{
    struct time stime;
    struct date sday;
} as_now, updated;

int main (void)
{
   struct dateandTime updated; 

   struct dateandTime ClockUpdate (struct dateandTime x);   
   struct dateandTime get_date_and_time (void);

   get_date_and_time ();
   updated = ClockUpdate (as_now);

   printf ("The Updated time is  %.2d : %.2d : %.2d \n", updated.stime.hour, updated.stime.minute, updated.stime.second);
   printf ("The Updated day is %.2d : %.2d : %.2d \n", updated.sday.day, updated.sday.month, updated.sday.year);

   return 0;
}

struct dateandTime get_date_and_time (void)
{
    printf("This program updates the time and date\n\n");

    printf("Enter the date (dd mm yyyy)\n");
    scanf ("%d   %d   %d", &as_now.sday.day, &as_now.sday.month, &as_now.sday.year);
    
    printf("Enter the time hh mm ss\n");
    scanf ("%d   %d   %d", &as_now.stime.hour, &as_now.stime.minute, &as_now.stime.second);

    return as_now;
}

struct time timeupdate (struct time now)
{
    ++now.second;

    if (now.second == 60)
    {
        now.second = 0;
        ++now.minute;
    }

    if (now.minute == 60)
    {
        now.minute = 0;
        ++now.hour;
    }

    if (now.hour == 24)
    {
        now.hour = 0;
    }

    return now;

}

struct date updatedate (struct date today)
{
    struct date tommorrow;
    int numberofdays(struct date d);   

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

struct dateandTime ClockUpdate (struct dateandTime x)
{
   struct time timeupdate (struct time now);
   struct date updatedate (struct date today);

   x.stime = timeupdate (as_now.stime);

   if (x.stime.hour == 0 && x.stime.minute == 0 && x.stime.second == 0 )
   x.sday = updatedate (as_now.sday);

   return x;
   
}
