#include <stdio.h>

struct entry  
{
    int values;
    struct entry *next;
}n1, n2, n3, dummyPointer;

int main (void)
{
    void removeEntry (struct entry *removeAfter);

    dummyPointer.next = &n1;
    n1.values = 100;
    n1.next = &n2;

    n2.values = 200;
    n2.next = &n3;

    n3.values = 300;
    n3.next = (struct entry *)0;

    removeEntry (&n1);
    removeEntry (&dummyPointer);

    while (dummyPointer.next != (struct entry *)0)
    {
        printf ("The value of the current entry is %d \n", dummyPointer.next -> values);
        dummyPointer.next = dummyPointer.next -> next;
    }
}

void removeEntry (struct entry *removeAfter)
{
    if (removeAfter -> next == (struct entry *)0)
    return;
    
    removeAfter -> next = (removeAfter -> next) -> next;
}