#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int main (int argc, char *argv[])
{
    int exit_status = EXIT_SUCCESS;
    int Checksum = 0;
    union 
    {
        unsigned char mock_network_data [16];
        struct __attribute__((packed))
        {
            unsigned short Match_ID;
            char Home_Team [3];
            char Away_Team [3];
            unsigned char Home_Score;
            unsigned char Away_Score;
            unsigned char Status ;
            float Possession;
            unsigned char Checksum;
        };
    } live_match;

     if ( argc != 2 )
    {
        fprintf (stderr, "No word typed on the command line.\n");
        
        return EXIT_FAILURE;
    }

    FILE  *match_data = fopen (argv[1], "rb");

    if (match_data == NULL)
    {
        fprintf (stderr, "Error opening match_data.bin\n");
        return EXIT_FAILURE;
    }

    size_t ret = fread(live_match.mock_network_data, ARRAY_SIZE(live_match.mock_network_data), sizeof(*live_match.mock_network_data), match_data);

    if (ret != sizeof(*live_match.mock_network_data))
    {
        fprintf(stderr, "fread() failed: %zu\n", ret);
        exit(EXIT_FAILURE);
    }


    for ( int i = 0; i < 15 ; i++ )
    {
        Checksum += live_match.mock_network_data[i];
    }

    if ( Checksum % 256 != live_match.mock_network_data[15])
    {
        printf ("Corrupted packet.packet dropped!!!\n");
        exit_status = EXIT_FAILURE;
        goto cleanup;
        
    }

    printf("%.3s\t vs\t %.3s\n",live_match.Home_Team, live_match.Away_Team); 

    if ((live_match.Status & 0x04) != 0)
    printf ("The match is under VAR Review\n");

    else if ((live_match.Status & 0x01) != 0)
    printf ("Firsthalf taking place\n");

    else if ((live_match.Status & 0x02) != 0)
    printf ("Secondhalf is in play\n");

    else
    printf ("Full-time\n");

    cleanup:

    fclose(match_data);

    return exit_status;

}  

