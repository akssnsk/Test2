#include <stdio.h>

int main()
{
    printf("this is \\/* \"a string\" */\\ with escaped chars");
    printf("\n");

    printf("this is \\/* \"a string\" */\\ with escaped chars");
    printf("\n");

    printf("this is \\/* \"a tricky string */\\ with escaped chars");
    printf("\n");

    printf("this is \\/* \"another tricky string /*\" \\ with escaped */ chars");
    printf("\n");
}