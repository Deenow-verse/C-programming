#include <stdio.h>

int main (void)
{
    FILE *exercise2_0, *read;
    int ratingcounters [11], i, response;
    exercise2_0 = fopen("survey_results.txt", "w");
    read = fopen ("survey_data.txt", "r");

    for (i = 1; i <= 10; ++i)
    {
        ratingcounters [i] = 0;
    }
    
     if (read == NULL )
    {
        fprintf (stderr, "Can't open survey_data.txt for reading\n");
        return 1;
    }

    
    while (fscanf (read, "%i", &response) != EOF) 
    {
        if (response < 1 || response > 10)
        printf ("Bad response: %d\n", response);
            
        else 
        ++ratingcounters[response];
    }
    
    
    if (exercise2_0 == NULL )
    {
        fprintf (stderr, "Can't open survey_results.txt for writing\n");
        return 1;
    }

    fprintf ( exercise2_0 ,"\n\nRatings      Number of response\n");
    fprintf ( exercise2_0 ,"------------    --------------------\n");

    for (i = 1; i <= 10; ++i)
    fprintf (exercise2_0, "%4i%14i\n", i, ratingcounters [i]);
   

    fclose (exercise2_0);
    fclose (read);
    

return 0;        

}