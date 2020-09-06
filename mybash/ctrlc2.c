#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <signal.h>

void ouch(int sig)
{
    printf("i get the sig = %d\n",sig);
    //signal(SIGINT,SIG_DFL);
}

int main()
{
    struct sigaction act;
    act.sa_handler = ouch;
    sigemotyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT,&act,0);

    while(1)
    {
        printf("Hello World\n");
        sleep(1);
    }
    exit(0);
}
