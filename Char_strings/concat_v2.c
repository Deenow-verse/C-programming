#include <stdio.h>

int main (void)
{
    void concat (char result [], const char str1 [], const char str2 []);
    const char s1 [] = { "Test " };
    const char s2 [] = { "Works." };
    char s3 [20];

    concat (s3, s1, s2);
    printf ("%s\n", s3);

    return 0;

}

void concat (char result [], const char str1 [], const char str2 [])
{
    int i, j, n;

    for (i = 0; ; ++i)
    {
        result [i] = str1 [i];
        if (str1 [i] == '\0')
            {
                n = i;
                break;
            }
    }

    for (j = 0; ; ++j)
    {
        result [n + j] = str2 [j];
        if (str2 [j] == '\0')
        {
            result [n + j] = '\0';
            break;
        }
    }

}