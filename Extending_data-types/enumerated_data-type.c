#include <stdio.h>

int main (void)
{
    enum month {January = 1, February, March, April, May, June, July, August, September, October, November, December};
    enum month aMonth;
    int days;
    
    printf ("Enter the number of number *NOTE (it should be between 1-12)\n");
    int temp_month;
    scanf ("%i", &temp_month);
    aMonth = temp_month; 

    switch (aMonth)
    {
        case January :
        case March:
        case May :
        case July :
        case August :
        case October : 
        case December :

        days = 31;
        break;

        case April :
        case June :
        case September :
        case November :

        days = 30;
        break;

        case February :

        days = 28;
        break;

        default :

        printf ("Entered a wrong month");
        days = 0;
        break;
    }

    if (days != 0)
    printf ("The number of days in this month is %i\n",days);

    if ( aMonth == February )
    printf ("...or %i if it's a leap year\n", days + 1);

    return 0;

}