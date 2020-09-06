#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <signal.h>

void func(int sig)
{
    printf("i get the sig = %d\n",sig);
    //signal(SIGINT,SIG_DFL);
}

int main()
{
    signal(SIGINT,func);
   // signal(SIGINT,SIG_IGN);
   // signal(SIGINT,SIG_DFL);
    while(1)
    {
        printf("Hello World\n");
        sleep(1);
    }
    exit(0);
}
