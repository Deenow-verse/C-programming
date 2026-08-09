#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
    #define LOG(fmt, ...) fprintf (stderr, "[%s : %s : line%d]" fmt" \n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#else
    #define LOG(fmt, ...)
#endif

int calculate_data(int multiplier);

int main (void)
{
    int dice_roll;

    LOG("Checking the value of the uninitialized dice_roll: %d", dice_roll);

    LOG("Testing the printf output: %d", calculate_data (12));
    printf ("Make %d steps\n", calculate_data (12));

    return 0;

}

int calculate_data(int multiplier)
{
    int outcome;

    LOG("Starting calculation with multiplier: %d", multiplier);

    outcome = 12 * multiplier;

    LOG("The product is : %d", outcome);

    LOG("The return value is : %d", outcome % 6);

    return outcome % 6;

}