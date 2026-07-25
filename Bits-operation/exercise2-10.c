#include <stdio.h>
#include <stdbool.h>

int shift (signed int value, int n);
bool is_arithmetic_shift(signed int test_val, int n);

int main (void)
{
    signed int w1 = -190, w2 = -0444, shifted_value;

    shifted_value = shift (w1, 5);
    if (is_arithmetic_shift (shifted_value, 5))
    {
        printf("This first test shows My computer uses an Arithmetic Right Shift! as shown by the output in octal\n");
        printf ("%o\n\n", shifted_value);
    }

    else
    {        
        printf("This first test shows My computer uses a Logical Right Shift! as shown by the output in octal\n");
        printf ("%o\n\n",shifted_value);
    }
    
    shifted_value = shift (w2, 4);
    if (is_arithmetic_shift (shifted_value, 4))
    {
        printf("This second test shows My computer uses an Arithmetic Right Shift! as shown by the output in octal\n");
        printf ("%o\n\n", shifted_value);
    }

    else
    {        
        printf("This second test shows My computer uses a Logical Right Shift! as shown by the output in octal\n");
        printf ("%o\n\n", shifted_value);
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