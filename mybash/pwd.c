#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
 
int main()
{
    char buff[256] = {0};
 
    getcwd(buff,256);    //获得当前路径
 
    printf("mypwd:%s\n",buff);    //输出路径
 
    exit(0);
}
