#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main (void)
{
    int fetch_status, exit_status = EXIT_SUCCESS;
    float time_up ;
    FILE *sensor_data;
    sensor_data = fopen ("/proc/uptime", "r");

    if (sensor_data == NULL)
    {
        perror ("Error opening file");
        return EXIT_FAILURE;
    }

    errno = 0;
    fetch_status = fscanf (sensor_data, "%f", &time_up);
    
    if (fetch_status == 1)
    printf ("System Uptime: %.2f seconds\n", time_up); 

    else if (errno != 0)
    {
        perror ("scanf failed");
        exit_status = EXIT_FAILURE;
    }
    
    else
    {
        fprintf (stderr, "No data read from file\n");
        exit_status = EXIT_FAILURE;
    }

    fclose (sensor_data);
    return exit_status;
}