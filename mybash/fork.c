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
    char *s=NULL;
    int n = 0;

    signal(SIGCHLD,func);
    pid_t pid = fork();
    assert(-1!=pid);
    
    if(pid = 0)
    {

    }

    exit(0);
}
