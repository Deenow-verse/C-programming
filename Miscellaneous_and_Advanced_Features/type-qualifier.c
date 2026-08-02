#include <stdio.h>
#include <stdlib.h>

void poll_sensor( volatile int *sensor_port, int * restrict display_buffer, int * restrict logger_buffer, register int iterations);

int main (void)
{
    int dummy_sensor = 42;
    int display_buffer[5] = {0};
    int logger_buffer[5] = {0};

    poll_sensor(&dummy_sensor, display_buffer, logger_buffer, 5);

    printf("Display Buffer: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", display_buffer[i]);
    }

    printf("\nLogger Buffer: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", logger_buffer[i]);
    }
    printf("\n");

    return (EXIT_SUCCESS);
}

void poll_sensor( volatile int *sensor_port, int * restrict display_buffer, int * restrict logger_buffer, register int iterations)
{ int sensor_value ;
    for (register int i = 0; i < iterations; i++)
    {
        sensor_value = 2 * (*sensor_port); 
        display_buffer[i] = sensor_value;
        logger_buffer[i] = sensor_value;
    }
}