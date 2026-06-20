#include <stdio.h>

struct time 
{
    int hour;
    int minute;
    int second;
};

int main (void)
{
    struct time timeupdate (struct time now);
    struct time currenttime, nexttime;

    printf ("Enter the time (hh mm ss)");
    scanf ("%d : %d : %d", &currenttime.hour, &currenttime.minute, &currenttime.second);

    nexttime = timeupdate (currenttime);

    printf ("Updated time is %.2i : %.2i : %.2i\n", nexttime.hour, nexttime.minute, nexttime.second);

    return 0;
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