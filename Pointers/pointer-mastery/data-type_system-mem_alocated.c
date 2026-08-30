#include <stdio.h>

int main (void)
{
    printf ("An int in this system is alocated %zu bytes of memory\n", sizeof (int));
    printf ("A float in this system is alocated %zu bytes of memory\n", sizeof (float));
    printf ("A double in this system is alocated %zu bytes of memory\n", sizeof (double));
    printf ("A char in this system is alocated %zu bytes of memory\n", sizeof (char));
    printf ("A long int in this system is alocated %zu bytes of memory\n", sizeof (long int));
    printf ("A 'long long int' in this system is alocated %zu bytes of memory\n", sizeof (long long int));
    printf ("An 'unsigned int' in this system is alocated %zu bytes of memory\n", sizeof (unsigned int));
    printf ("An 'unsigned long int' in this system is alocated %zu bytes of memory\n", sizeof (unsigned long int));
    printf ("An 'unsigned long long int' in this system is alocated %zu bytes of memory\n", sizeof (unsigned long long int));
    printf ("An signed int in this system is alocated %zu bytes of memory\n", sizeof (signed int));
    printf ("An signed long int in this system is alocated %zu bytes of memory\n", sizeof (signed long int));
    printf ("An signed long long int in this system is alocated %zu bytes of memory\n", sizeof (signed long long int));
    printf ("An unsigned char in this system is alocated %zu bytes of memory\n", sizeof (unsigned char));
    printf ("An signed char in this system is alocated %zu bytes of memory\n", sizeof (signed char));
    printf ("An long double in this system is alocated %zu bytes of memory\n", sizeof (long double));
    
    return 0;
}