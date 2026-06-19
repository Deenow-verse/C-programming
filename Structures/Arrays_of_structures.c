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
    struct time testTimes[5] = { { 11, 59, 59 }, { 12, 0, 0 }, { 1, 29, 59 }, { 23, 59, 59 }, { 19, 12, 27 }};
    
    int i;
    for (i = 0; i < 5; ++i)
    {
        printf ("Time is %.2i : %.2i : %.2i", testTimes [i].hour, testTimes [i].minute, testTimes [i].second );

        testTimes [i]= timeupdate (testTimes[i]);
        printf (".... one second later is %.2d : %.2d : %.2d\n", testTimes [i].hour, testTimes [i].minute, testTimes [i].second);
    }
        
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