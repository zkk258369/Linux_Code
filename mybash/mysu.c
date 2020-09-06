//mysu.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <assert.h>
 
int main(int argc,char *argv[])
{
    char *name = "root";    //默认指定要切换的用户是管理员用户
    if(argc == 2)    //当有两个参数的时候，说明su明后后边有指定要切换到的用户
    {
        name = argv[1];
    }
    struct passwd *p = getpwnam(name);    //获取用户信息
    if(p == NULL)
    {
        perror("su error!");
        exit(0);
    }
 
    pid_t pid = fork();    //复制进程
    assert(pid != -1);
 
    if(pid == 0)    //进人子进程
    {
        setgid(p->pw_gid);    //修改当前进程的gid
        setuid(p->pw_uid);    //修改当前进程的uid
        
        setenv("HOME",p->pw_dir,1);    //修改环境变量，指定当前处于要切换到的用户的家目录下
 
        execl(p->pw_shell,"p->pw_shell",(char*)0);    //用p进程的终端替换该进程，使当前处于p用户的shell下，完成切换功能
        perror("su execl errer!");
        exit(0);
    }
 
    wait(NULL);
    exit(0);    
}
