#include <stdio.h>

struct time
{
    int hour;
    int minute;
    int second;
}previous_time, time_elapsed, now;

int main (void)
{
    void getdates (void);
    struct time elapsed_time (struct time time1, struct time time2);

    getdates ();
    elapsed_time (previous_time, now );

    printf ("The elapsed time is %d  %d %d\n", time_elapsed.hour, time_elapsed.minute, time_elapsed.second);

}

void getdates (void)
{
       

    printf("This program finds the difference between two time,within the same day hence you'll be asked to provide two time\n\n");

    printf("Enter the first time hh mm ss\n");
    scanf ("%d   %d   %d", &previous_time.hour, &previous_time.minute, &previous_time.second);

       
    printf("Enter the second time (hh mm ss)\n");
    scanf ("%d   %d   %d", &now.hour, &now.minute, &now.second);
    
}

struct time elapsed_time (struct time time1, struct time time2)
{
    if (time1.hour >= time2.hour)
    time2.hour += 24;

    if (time2.second < time1.second)
    {

       time2.second += 60;
       time_elapsed.second = time2.second - time1.second;

       if (time2.minute >= 1 )
       time2.minute -= 1;

       else if(time2.minute < 1)
       {
        time2.minute += 59;
        time2.hour -= 1;
       }

    }
    else
    time_elapsed.second = time2.second - time1.second;

    if (time2.minute < time1.minute)
    {
        time2.minute += 60;
        time_elapsed.minute = time2.minute - time1.minute;

        time2.hour -= 1;
    }

    else
    time_elapsed.minute = time2.minute - time1.minute;

    time_elapsed.hour = time2.hour - time1.hour;   

    return time_elapsed;

}
