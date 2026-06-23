#include <stdio.h>

struct date 
{
    int day;
    int month;
    int year;
} The_Year;

struct name_of_day
{   
    char name [10];
};

const struct name_of_day Day [7] = {{'S', 'u', 'n', 'd', 'a', 'y'}, {'M', 'o', 'n', 'd', 'a', 'y'}, {'T', 'u', 'e', 's', 'd', 'a','y'}, {'W', 'e', 'd', 'n', 'e', 's', 'd', 'a', 'y'}, {'T', 'h', 'u', 'r', 's', 'd', 'a', 'y'}, {'F', 'r', 'i', 'd', 'a', 'y'}, {'S', 'a', 't', 'u', 'r', 'd','a', 'y'}};
int day;

int main (void)
{
    void getdates (void);
    struct name_of_day day_of_the_week (void);

    getdates();
    day_of_the_week ();

    printf ("The day is ");
    for (int i = 0; i < 10; ++i)
    printf ("%c", Day[day].name[i]);

    printf ("\n");

    return 0;
}

void getdates (void)
{
       

    printf("This program displays the name of the week for the date you provide\n\n");

    printf("Enter the date (dd mm yyyy)\n");
    scanf ("%d   %d   %d", &The_Year.day, &The_Year.month, &The_Year.year);
    
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

struct name_of_day day_of_the_week (void)
{
    int result, N;
    int elapsed_days (struct date x);

    N = elapsed_days (The_Year);

    result = N - 621049;
    day = result % 7;

    return Day [day];

} 