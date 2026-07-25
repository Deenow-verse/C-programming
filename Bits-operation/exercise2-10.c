#include <stdio.h>
#include <stdbool.h>

int shift (signed int value, int n);
bool is_arithmetic_shift(signed int test_val, int n);

int main (void)
{
    signed int w1 = -190, w2 = -0444;

    shift (w1, 5);
    if (is_arithmetic_shift (w1, 5))
    {
        printf("This first test shows My computer uses an Arithmetic Right Shift! as shown by the output in octal\n");
        printf ("%o\n\n", w1);
    }

    else
    {        
        printf("This first test shows My computer uses a Logical Right Shift! as shown by the output in octal\n");
        printf ("%o\n\n", w1);
    }
    
    shift (w2, 4);
    if (is_arithmetic_shift (w2, 4))
    {
        printf("This second test shows My computer uses an Arithmetic Right Shift! as shown by the output in octal\n");
        printf ("%o\n\n", w2);
    }

    else
    {        
        printf("This second test shows My computer uses a Logical Right Shift! as shown by the output in octal\n");
        printf ("%o\n\n", w2);
    }
       
    return 0;
}

signed int shift (signed  int value, int n)
{
  
   value >>= n;
      
   return value;
}

bool is_arithmetic_shift(signed int test_val, int n)
{
    test_val = -1;

    int shifted_val = test_val >> n;

    if (shifted_val < 0) 
    {
        return true; 
    }

    else 
    {
        return false;
    }
    
}