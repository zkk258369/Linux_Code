#include <stdio.h>
#include <stdlib.h>

void main()
{
    fputs("\x1b[2J\x1b[H", stdout);
    //exit(0);
}