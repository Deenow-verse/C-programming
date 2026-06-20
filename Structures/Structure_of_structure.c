#include <stdio.h>

int main (void)
{
    int i;
    struct month
    {
        int numberofdays;
        char name [3];
    };
    const struct month Months [12] =
    {{31, {'J', 'A', 'N'}}, {28, {'F','E','B'}}, {31, {'M', 'A', 'R'}}, {30, {'A', 'P', 'R'}}, {31, {'M', 'A', 'Y'}}, {30, {'J', 'U', 'N'}}, {31, {'J', 'U', 'L'}}, {31, {'A', 'U', 'G'}}, {30, {'S', 'E', 'P'}}, {31, {'O', 'C', 'T'}}, {30, {'N', 'O', 'V'}}, {31, {'D', 'E', 'C'}}};

    printf ("Month                                Number of Days\n");
    printf ("------                              ----------------");

    for (i = 0; i < 12; ++i )
    {
        printf ("")
    }
}