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
} ;

void ClockUpdate (struct dateandTime *x);   
void get_date_and_time (struct dateandTime *as_now);
void timeupdate (struct time *now);
void updatedate (struct date *today);
int numberofdays(struct date d);
bool isLeapYear (struct date d);


int main (void)
{
   struct dateandTime as_now; 

   get_date_and_time (&as_now);
   ClockUpdate (&as_now);

   printf ("The Updated time is  %.2d : %.2d : %.2d \n", as_now.stime.hour, as_now.stime.minute, as_now.stime.second);
   printf ("The Updated day is %.2d : %.2d : %.2d \n", as_now.sday.day, as_now.sday.month, as_now.sday.year);

   return 0;
}

void get_date_and_time (struct dateandTime *as_now)
{
    printf("This program updates the time and date\n\n");

    printf("Enter the date (dd mm yyyy)\n");
    scanf ("%d %d %d", &as_now->sday.day, &as_now->sday.month, &as_now->sday.year);

    do 
    {
        printf("Enter the time hh mm ss\n");
        scanf ("%d %d %d", &as_now->stime.hour, &as_now->stime.minute, &as_now->stime.second);

        if (as_now->stime.hour > 23 || as_now->stime.minute > 59 || as_now->stime.second > 59)
        {
            printf ("Invalid time. Please try again.\n\n");
        }
    } 
    while (as_now->stime.hour > 23 || as_now->stime.minute > 59 || as_now->stime.second > 59);
}

void timeupdate (struct time *now)
{
    ++now -> second;

    if (now -> second == 60)
    {
        now -> second = 0;
        ++now -> minute;
    }

    if (now -> minute == 60)
    {
        now -> minute = 0;
        ++now -> hour;
    }

    if (now -> hour == 24)
    {
        now -> hour = 0;
    }


}

void updatedate (struct date *today)
{
    if (today->day != numberofdays (*today))
        today->day = today->day + 1;

    else if (today->month == 12)
       {
            today->day = 1;
            today->month = 1;
            today->year = today->year + 1;    
        }    

    else     
        {   today->day = 1;
            today->month = today->month + 1;
        }
}

int numberofdays (struct date d)
{
    int days;    
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

void ClockUpdate (struct dateandTime *x)
{
   timeupdate (&x->stime);

   if (x->stime.hour == 0 && x->stime.minute == 0 && x->stime.second == 0 )
   {
       updatedate (&x->sday);
   }
   
}
