#include <stdio.h>

struct entry  
{
    struct entry *previous;
    int values;
    struct entry *next;
};

void removeEntry (struct entry *removeAfter);
void insertEntry (struct entry *insertAfter, struct entry *toInsert);

int main (void)
{
    struct entry n1, n2, n3, n2_3, StartPointer, EndPointer;
    struct entry *currentPointer;

    StartPointer.next = &n1;
    StartPointer.previous = (struct entry *)0;

    EndPointer.previous = &n3;
    EndPointer.next = (struct entry *)0;
 
    n1.previous = &StartPointer;
    n1.values = 100;
    n1.next = &n2;

    n2.previous = &n1;
    n2.values = 200;
    n2.next = &n3;

    n3.previous = &n2;
    n3.values = 300;
    n3.next = &EndPointer;

    n2_3.values = 250;

    printf ("The list after adding the new entry %d \n\n", n2_3.values);
    insertEntry (&StartPointer, &n2_3);

    currentPointer = StartPointer.next;
    while (currentPointer != &EndPointer)
    {
        printf ("The value of the current entry is %d \n", currentPointer -> values);
        currentPointer = currentPointer -> next;
    }

    printf ("\n\nRemoving the entry with value %d \n\n", n2.values);
    removeEntry (&n2);

    currentPointer = StartPointer.next;
    while (currentPointer != &EndPointer)
    {
        printf ("The value of the current entry is %d \n", currentPointer -> values);
        currentPointer = currentPointer -> next;
    }

    return 0;
   
}

void removeEntry (struct entry *remove)
{
    if (remove == (struct entry *)0 )
    return;

    remove -> previous -> next = remove -> next;
    remove -> next -> previous = remove -> previous;
   
}

void insertEntry (struct entry *insertAfter, struct entry *toInsert)
{
    if (insertAfter == (struct entry *)0 || toInsert == (struct entry *)0)
    return;

    toInsert -> next = insertAfter -> next;
    toInsert -> previous = insertAfter;
    insertAfter -> next -> previous = toInsert;
    insertAfter -> next = toInsert;
}