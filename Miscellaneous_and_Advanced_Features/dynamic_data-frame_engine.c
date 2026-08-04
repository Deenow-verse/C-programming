#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main (void)
{
    FILE *file;
    int exit_status = 0;
    struct record
    {
        int      id;
        int      age;
        float    metric_score;
    };

    int capacity = 2;
    int current_count = 0;

    if ( (file = fopen ("test", "r")) == NULL )
    {
        fprintf (stderr, "Can't write %p.\n", file);
        exit_status = 1;
    }    

    struct record *records_buf = (struct record *) (malloc (capacity*sizeof (struct record)));

    if (records_buf == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit_status = 1;
        goto end;
    }   
    
    int temp_id, temp_age; float temp_score;
    
    while (fscanf(file, "%d,%d,%f", &temp_id, &temp_age, &temp_score) != EOF)
    {
        if (current_count == capacity)
        {
            int new_capacity = capacity * 2;
            struct record *temp = realloc (records_buf, new_capacity *sizeof *records_buf);

            if (temp == NULL)
            {
                fprintf(stderr, "Memory allocation failed\n");
                exit_status = 1;
                goto end;
            }

            records_buf = temp;
            capacity = new_capacity;
        }

        records_buf[current_count].id = temp_id;
        records_buf[current_count].age = temp_age;
        records_buf[current_count].metric_score = temp_score;        
      
        ++current_count;
    }

    for (int ind = 0; ind < current_count; ++ind)
    {
        printf ("%d\t   %d\t   %.2f\n",  records_buf[ind].id,  records_buf[ind].age,  records_buf[ind].metric_score);
    }

    end:
    fclose (file);
    
    free (records_buf);

    return exit_status;

}    