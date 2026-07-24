#include <stdio.h>

int main (void)
{
    unsigned word1 = 0525u, word2 = 0707u, word3 = 0122u;

    printf ("%o  %o  %o\n", word1 & word2, word1 | word2, word1 ^ word2);
    printf ("%o  %o  %o\n", ~word1, ~word2, ~word3);
    printf ("%o  %o  %o\n", word1 ^ word1, word1 & ~word2, word1 | word2 | word3);
    printf ("%o  %o\n", word1 | word2 & word3, word1 | word2 & ~word3);
    printf ("%o  %o\n", ~(~word1 & ~word2), ~(~word1 | ~word2));

    word1 ^= word2;
    word2 ^= word1;
    word1 ^= word2;

    printf ("w1 = %o, w2 = %o, w3 = %o\n", word1, word2, word3);

    return 0;
}