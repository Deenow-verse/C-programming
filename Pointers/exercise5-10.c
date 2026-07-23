#include <stdio.h>

struct entry  
{
    struct entry *previous;
    int values;
    struct entry *next;
}n1, n2, n3, endPointer;

int main (void)
{
    n1.previous = (struct entry *)0;
    n1.values = 100;
    n1.next = &n2;

    n2.previous = &n1;
    n2.values = 200;
    n2.next = &n3;

    n3.previous = &n2;
    n3.values = 300;
    n3.next = (struct entry *)0;

    endPointer.previous = &n3;

    while (endPointer.previous != (struct entry *)0)
    {
        printf ("The value of the current entry is %d \n", endPointer.previous -> values);
        endPointer.previous = endPointer.previous -> previous;
    }

    return 0;

}