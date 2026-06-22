#include <stdio.h>

struct date 
{
    int day;
    int month;
    int year;
} previous_year, this_year; 

int main (void)
{
    int N_1, N_2, Number_of_elapsed_days;

    void getdates (void);
    int elapsed_days (struct date x);

    getdates();

    N_1 = elapsed_days (previous_year);
    N_2 = elapsed_days (this_year);

    Number_of_elapsed_days = N_2 - N_1;

    printf ("The elapsed days are %d\n", Number_of_elapsed_days);
}

void getdates (void)
{
       

    printf("This program finds the difference between two dates, hence you will be asked to provide 2 dates\n\n");

    printf("Enter the first date (dd mm yyyy)\n");
    scanf ("%d   %d   %d", &previous_year.day, &previous_year.month, &previous_year.year);

       
    printf("Enter the second date (dd mm yyyy)\n");
    scanf ("%d   %d   %d", &this_year.day, &this_year.month, &this_year.year);
    
}

int f (int year, int month)
{
   if (month <= 2)
    year -= 1;

    return year;

}

int g (int month)
{
    if (month <= 2)
    month += 13;

    else 
    month += 1;

    return month;
}

int elapsed_days (struct date x)
{
    int N;

    int f (int year, int month);
    int g (int month);

    N = 1461 * f (x.year, x.month) / 4 + 153 * g (x.month) / 5 + x.day;

    if ((x.year == 1900 && x.month <= 2) || (x.year == 1800 && x.month >=3 ) || (x.year < 1900 && x.year > 1800))
    N += 1; 
    
    else if ((x.year == 1800 && x.month <= 2) || (x.year == 1700 && x.month >=3 ) || (x.year < 1800 && x.year > 1700))
    N += 2;

    return N;
}