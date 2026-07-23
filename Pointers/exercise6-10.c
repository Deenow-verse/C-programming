#include <stdio.h>

struct entry  
{
    struct entry *previous;
    int values;
    struct entry *next;
};

int main (void)
{
    int removeEntry (struct entry *removeAfter);
    void insertEntry (struct entry *insertAfter, struct entry *toInsert);
    struct entry n1, n2, n3, n2_3, StartPointer, EndPointer;

    StartPointer.next = &n1;
    EndPointer.previous = &n3;
 
    n1.previous = (struct entry *)0;
    n1.values = 100;
    n1.next = &n2;

    n2.previous = &n1;
    n2.values = 200;
    n2.next = &n3;

    n3.previous = &n2;
    n3.values = 300;
    n3.next = (struct entry *)0;

    insertEntry (&n2_3, &n2_3);

    while (StartPointer.next != (struct entry *)0)
    {
        printf ("The value of the current entry is %d \n", StartPointer.next -> values);
        StartPointer.next = StartPointer.next -> next;
    }

    int result = removeEntry (&n2);

    if (result == -1)
    {
        printf ("The entry cannot be removed as it is the first or last entry or not in the list \n");
    }

    while (StartPointer.next != (struct entry *)0)
    {
        printf ("The value of the current entry is %d \n", StartPointer.next -> values);
        StartPointer.next = StartPointer.next -> next;
    }

    return 0;
   
}

int removeEntry (struct entry *remove)
{
    if (remove -> next == (struct entry *)0 || remove -> previous == (struct entry *)0)
    return -1; 
    
    remove -> previous -> next = remove -> next;
    remove -> next -> previous = remove -> previous;
   
}

void insertEntry (struct entry *insertAfter, struct entry *toInsert)
{
   insertAfter -> next = toInsert;
   toInsert -> previous = insertAfter;
}