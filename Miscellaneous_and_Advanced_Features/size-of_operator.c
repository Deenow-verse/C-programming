#include <stdio.h>

#define MY_SIZEOF(var) ((char*)(&var + 1)) - ((char*)(&var)) 

int main(void)
{
    int x;
    double d;
    char c;
    int arr[10];

    printf("sizeof(int)     = %zu\n", MY_SIZEOF(x));
    printf("sizeof(double)  = %zu\n", MY_SIZEOF(d));
    printf("sizeof(char)    = %zu\n", MY_SIZEOF(c));
    printf("sizeof(int[10]) = %zu\n", MY_SIZEOF(arr));

    return 0;
}