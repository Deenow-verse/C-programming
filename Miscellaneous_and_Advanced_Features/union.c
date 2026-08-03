#include <stdio.h>
#include <string.h>

#define kTableEntries 100
int main (void)
{
    char letter;
    char string[12];
    char string_name[100][12];
    enum symbolType { INTEGER, FLOATING, CHARACTER };
    string [11] = '\0';
    string_name[99][11] = '\0';
    
    struct
    { 
        char                 *name;
        enum symbolType      type;
        union 
        {
            int    i;
            float  f;
            char   c;
        }                    data;
        
    }                        table [kTableEntries];


    for (int i = 0; i < kTableEntries - 1; ++i )
    {
        letter = 'a' + (i % 26);

        for (int counter = 0; counter < 11; ++counter)
        {
            int temp_letter = letter;

            if ( temp_letter == 'z' || temp_letter > 'z')
            temp_letter -= 26;
        
            else if (temp_letter < 'a')
            temp_letter += 25;

            else
            temp_letter +=  5;

            letter = temp_letter % 26 + 'a';
            string[counter] = letter;
        }
        strcpy(string_name[i], string);
        table[i].name = string_name [i];

        if (i % 3 == 0)
        {
            table[i].type = INTEGER;
            table[i].data.i = 12 * i;
        }
        else if (i % 3 == 1)
        {
            table[i].type = FLOATING;
            table[i].data.f = 17.3f * i;
        }
        else
        {
            table[i].type = CHARACTER;
            table[i].data.c = 'a' + (i % 26);
        }
    }

    table[kTableEntries - 1].name = NULL;


    int j = 0;
    while (table[j].name != NULL)
    {
        printf ("%s  ", table[j].name);

        switch (table[j].type)
        {
            case INTEGER:
            printf ("%i\n", table[j].data.i);
            break;
            
            case FLOATING:
            printf ("%f\n", table[j].data.f);
            break;
            
            case CHARACTER:
            printf ("%c\n", table[j].data.c);
            break;
            
            default:
            printf ("Unknown type (%i), element %i\n", table[j].type, j );
            break;
        }

        ++j;

    }

    return 0;

}