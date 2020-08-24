//mybash.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <pwd.h>

#define PATH "/home/zkk/LinuxClass/190420实现mybash/"


#define MAX_ARG 10

void printfinfo()
{
    char *s = "$";
    int id = getuid();//获取用户，用来判断是管理员模式，还是用户模式
    if( id == 0 )
    {
        s = "#";
    }

    struct passwd * pt = getpwuid(id);
    if( pt == NULL )
    {
        printf("mybash>>");
        fflush(stdout);
        return;
    }

    char hostname[64] = {0};
    gethostname(hostname, 64);//获取主机名字

    char path[256] = {0};
    getcwd(path, 256);
    char * q = "/";
    char * p = strtok(path, "/");
    while( p != NULL )
    {
        q = p;
        p = strtok(NULL, "/");
    }

    printf("[%s@%s %s]%s ",pt->pw_name,hostname,q,s);
    fflush(stdout);
}

int main()
{
    while(1)
    {
        char buff[128] = {0};//存放输入的参数和命令
        //printf("[stu@ localhost ~]$");
        //fflush(stdout);//刷新输出缓存区
        printfinfo();//输出终端用户名

        fgets(buff, 128, stdin);//可以输入命令的例子： ls, ps -f, cp a.c b.c
        buff[strlen(buff)-1] = 0;//给输入的命令后加\0

        char *myargv[MAX_ARG] = {0};

        int i = 0;
        char *s = strtok(buff, " ");//以空格为分界符分割字符
        char *cmd_name = s;//命令名字
        while( s != NULL )
        {
            myargv[i++] = s;
            s = strtok(NULL, " ");
        }

        if(cmd_name == NULL)
        {
            continue;
        }

        if(strcmp(cmd_name,"cd") == 0)
        {
            if( myargv[1] == NULL )
            {
                continue;
            }
            if( chdir(myargv[1]) == -1 )
            {
                perror("cd error");
            }
            chdir(myargv[1]);
            continue;
        }
        else if(strcmp(cmd_name, "exit") == 0)
        {
            break;
        }
        else
        {
            pid_t pid = fork();
            if( pid ==-1 )
            {
                perror("fork error");
                continue;
            }

            if( pid == 0 )
            {
                char path[128] = {0};
                if( strncmp(cmd_name, "./", 2) != 0 && strncmp(cmd_name, "/", 1) != 0 )
                {
                    strcpy(path,PATH);
                }
                strcat(path,cmd_name);
                execvp(path, myargv);
                perror("execvp error");
                exit(0);
            }
            wait(NULL);
        }
    }


    exit(0);
}
