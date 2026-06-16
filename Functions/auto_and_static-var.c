#include <stdio.h> 

int main (void)
{
    int i;
    void auto_static (void);

    for (i = 0; i < 5; ++i )
    {
        auto_static ();
    }

    return 0;
}

void auto_static (void)
{
    int auto_var = 1;
    static int static_var = 1;

    printf ("automatic = %i static = %i\n", auto_var, static_var);

    ++auto_var;
    ++static_var;
}