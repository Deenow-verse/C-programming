#include <stdio.h>

struct related
{
    struct related *previous;
    int values;
    struct related *next;
};

void sort3 (struct related *n1, struct related *n2, struct related *n3);

int main (void)
{
    struct related n1, n2, n3;
    struct related *currentPointer;

    n1.previous = (struct related *)0;
    n1.values = 100;
    n1.next = &n2;

    n2.previous = &n1;
    n2.values = 200;
    n2.next = &n3;

    n3.previous = &n2;
    n3.values = 300;
    n3.next = (struct related *)0;

    printf ("The values before undergoing the sorting process:\n");
    
    currentPointer = &n1;
    while (currentPointer != (struct related *)0)
    {
        printf (" %d \n", currentPointer -> values);
        currentPointer = currentPointer -> next;
    } 

    sort3 (&n1, &n2, &n3);

    printf ("\n\nThe values after undergoing the sorting process:\n");
    
    currentPointer = &n1;
    while (currentPointer != (struct related *)0)
    {
        printf (" %d \n", currentPointer -> values);
        currentPointer = currentPointer -> next;
    }

    return 0;
}

void sort3 (struct related *n1, struct related *n2, struct related *n3)
{    
    if (n1 -> values < n2 -> values)
    {
        n1 -> next = n2 -> next;
        n2 -> next = n1;
        n2 -> previous = n1 -> previous;
        n1 -> previous = n2;
    }

    if (n1 -> values < n3 -> values)
    {
        n1 -> next = n3 -> next;
        n3 -> next = n1;
        n3 -> previous = n2 -> previous;
        n1 -> previous = n3;
    }

    if (n2 -> values < n3 -> values)
    {
       n2 -> next = n3 -> next;
       n3 -> next = n2;
       n3 -> previous = n2 -> previous;
       n2 -> previous = n3;
    }
}