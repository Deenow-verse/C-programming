#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    int x_plane, y_plane, z_plane;
    int (*grid)[180][180] = malloc(sizeof( int[180][180][180]));
    grid [89][89][89] = 99;
    
    if (grid == NULL) {
        perror("malloc");
        return (EXIT_FAILURE);
    }

    for (x_plane = 0; x_plane < 180; x_plane++)
    {
        for (y_plane = 0; y_plane < 180; y_plane++)
        {
            for (z_plane = 0; z_plane < 180; z_plane++)
            {
                if (grid[x_plane][y_plane][z_plane] == 99)
                {
                    printf ("The co-ordinate of the target is (%d, %d, %d).\n", x_plane, y_plane, z_plane);
                    goto search_Completed;
                }
            }
        }
    }

    search_Completed: printf ("Found the co-ordinate of the target.\n");

    printf ("JUmped successfully hence Exiting the program.\n");

    free(grid);

    return (EXIT_SUCCESS);
}