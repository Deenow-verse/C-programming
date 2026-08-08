#include <stdio.h>
#include <stdlib.h>

#define DEBUG(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)

int process (int i1, int i2);

int main (int argc, char * argv [])
{
    int arc1 = 0, arc2 = 0;

    if (argc > 1)
    arc1 = atoi (argv [1]);

    if (argc == 3)
    arc2 = atoi (argv [2]);

    DEBUG ("process %i arguments\n", argc - 1);
    DEBUG ("arc1 = %i\t arc2 =%i\n", arc1, arc2);

    printf ("%d\n", process (arc1, arc2));

    return 0;
}

int process (int i1, int i2)
{
    int val;

    DEBUG ("process (%i, %i)\n", i1, i2);

    val = i1 * i2;

    DEBUG ("return %i\n", val);

    return val;

}