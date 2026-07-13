#include <stdio.h>

int main (void)
{
    void test (int *int_pointer);
    int i = 50, *p = &i;

    printf ("Before the call to test i = %i\n", i);

    test (p);

    printf ("After the calling the test i = %d\n", i);

    return 0;
}

void test (int *int_pointer)
{
    *int_pointer = 100;
}