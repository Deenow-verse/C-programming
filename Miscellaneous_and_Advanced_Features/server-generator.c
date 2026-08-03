#include <stdio.h>

int main(void) {
    // 16-byte raw hex representation of a live match (ARS vs MUN)
    unsigned char mock_network_data[16] = {
        0x01, 0x00,             // Match ID: 1
        'A', 'R', 'S',          // Home Team
        'M', 'U', 'N',          // Away Team
        0x02,                   // Home Score: 2
        0x01,                   // Away Score: 1
        0x06,                   // Status: 0x02 (2nd Half) | 0x04 (VAR) = 0x06
        0x66, 0x66, 0x0E, 0x42, // Possession: 35.6f
        0x50                    // Checksum (Valid)
    };

    FILE *out = fopen("match_data.bin", "wb");
    if (out != NULL) {
        fwrite(mock_network_data, sizeof(unsigned char), 16, out);
        fclose(out);
        printf("Server: match_data.bin generated successfully.\n");
    }
    return 0;
}