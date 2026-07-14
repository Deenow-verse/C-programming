#include <stdio.h>

struct entry  
{
    int values;
    struct entry *next;
}n1, n2, n3;

int main (void)
{
    void insertEntry (struct entry *insertAfter , struct entry *toInsert);

    n1.values = 100;
    n1.next = &n2;

    n2.values = 200;
    n2.next = &n3;

    n3.values = 300;
    n3.next = (struct entry *)0;

    struct entry n2_3;

    insertEntry (&n2, &n2_3);

    printf ("The value of n2_3 is %d and n3 comes after it with a value %d and n2 before it pointing the next from n2 gives the value of n2 as %d \n", n2_3.values, n2_3.next -> values, n2.next -> values);
}

void insertEntry (struct entry *insertAfter , struct entry *toInsert)
{
    toInsert -> next = insertAfter -> next;
    insertAfter -> next = toInsert;
    toInsert -> values = 250;
}