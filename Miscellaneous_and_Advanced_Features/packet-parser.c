#include <stdio.h>

int main (void)
{
    union 
    {
        unsigned char raw_buffer[6];
        struct __attribute__((packed))
        {
            unsigned char device_id;
            unsigned char sensor_type;
            float temperature;
        };
    }NetworkFrame;

    NetworkFrame.raw_buffer[0] = 0x04;
    NetworkFrame.raw_buffer[1] = 0x01;
    NetworkFrame.raw_buffer[2] = 0x00;
    NetworkFrame.raw_buffer[3] = 0x00;
    NetworkFrame.raw_buffer[4] = 0xF0;
    NetworkFrame.raw_buffer[5] = 0x41;

    printf (" Device ID: %d\t Sensor Type: %d\t Temperature: %.1f\n", NetworkFrame.device_id, NetworkFrame.sensor_type, NetworkFrame.temperature);

    return 0; 
}
