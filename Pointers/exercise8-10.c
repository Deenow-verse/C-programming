#include <stdio.h>

struct related
{
    struct related *previous;
    int values;
    struct related *next;
};

void sort3 (int *n1, int *n2, int *n3);

int main (void)
{
    struct related n1, n2, n3;
    struct related *currentPointer;

    n1.previous = (struct related *)0;
    n1.values = 500;
    n1.next = &n2;

    n2.previous = &n1;
    n2.values = 200;
    n2.next = &n3;

    n3.previous = &n2;
    n3.values = 100;
    n3.next = (struct related *)0;

    printf ("The values before undergoing the sorting process:\n");
    
    currentPointer = &n1;
    while (currentPointer != (struct related *)0)
    {
        printf (" %d \n", currentPointer -> values);
        currentPointer = currentPointer -> next;
    } 

    sort3 (&n1.values, &n2.values, &n3.values);

    printf ("\n\nThe values after undergoing the sorting process:\n");
    
    currentPointer = &n1;
    while (currentPointer != (struct related *)0)
    {
        printf (" %d \n", currentPointer -> values);
        currentPointer = currentPointer -> next;
    }

    return 0;
}

void sort3 (int *n1, int *n2, int *n3)
{   
   int temp;

   if (*n1 > *n2)
   {
    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
   }

   if (*n1 > *n3)
   {
    temp = *n1;
    *n1 = *n3;
    *n3 = temp;
   }

   if (*n2 > *n3)
   {
    temp = *n2;
    *n2 = *n3;
    *n3 = temp;
   }

}