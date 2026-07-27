#include <stdio.h>

#define YES 1
#define NO  0

int is_even (int number);

int main (void)
{
    if (is_even (17) == YES)
    printf ("yes\n");
    else 
    printf ("no\n");

    if (is_even (20) == YES)
    printf ("yes\n");
    else
    printf ("no\n");

    return 0;
}

int is_even (int number)
{
    int answer;

    if (number % 2 == 0)
    answer = YES;
    
    else 
    answer = NO;

    return answer;
}