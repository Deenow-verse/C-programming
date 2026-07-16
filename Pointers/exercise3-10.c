#include <stdio.h>

struct entry  
{
    int values;
    struct entry *next;
}n1, n2, n3, dummyPointer;

int main (void)
{
    void insertEntry (struct entry *insertAfter , struct entry *toInsert);

    dummyPointer.next = &n1;
    n1.values = 100;
    n1.next = &n2;

    n2.values = 200;
    n2.next = &n3;

    n3.values = 300;
    n3.next = (struct entry *)0;

    struct entry n2_3, newStart;
    n2_3.values = 250;
    newStart.values = 50;

    insertEntry (&n2, &n2_3);
    insertEntry (&dummyPointer, &newStart);

    while (dummyPointer.next != (struct entry *)0)
    {
        printf ("The value of the current entry is %d \n", dummyPointer.next -> values);
        dummyPointer.next = dummyPointer.next -> next;
    }
}

void insertEntry (struct entry *insertAfter , struct entry *toInsert)
{
    toInsert -> next = insertAfter -> next;
    insertAfter -> next = toInsert;
}  