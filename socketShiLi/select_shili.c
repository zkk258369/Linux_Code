/*
 * select 示例
 *
*/ 
#include<stdio.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/time.h>

#define STDIN 0

int main()
{

    fd_set fdset;
    int fd = STDIN;
    while(1)
    {

        FD_ZERO(&fdset);//清空集合
        FD_SET(fd,&fdset);
        
        struct timeval tv = {
            5,0};

            int n = select(fd+1, &fdset, NULL, NULL, &tv);
            if(n == -1)
            {

                perror("select error");
            }
            else if(n == 0)
            {

                printf("time out\n"); 
            }
            else
            {

                if(FD_ISSET(fd, &fdset))
                {

                    char buff[128] = {
                        0};
                        read(fd, buff, 127);
                        printf("read:%s\n",buff);
                }
            }
    }
    
    exit(0);
}
