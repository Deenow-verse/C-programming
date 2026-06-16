// program to calculate the absolute value of an integer
#include <stdio.h>

int main(void) {
    int number;
    printf("Enter your number: ");
    scanf("%d", &number);
    
    if (number < 0) {
        number = -number; 
        } 
        printf("The absolute value is: %d\n", number);        

        return 0;

}