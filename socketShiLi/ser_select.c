#include<stdio.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<string.h>

#define MAXFD 10

void fds_init(int *fds)
{
    int i = 0;
    for(; i<MAXFD; ++i)
    {
        fds[i] = -1;
    }
}

void fds_add(int *fds, int fd)
{
    int i = 0;
    for(; i<MAXFD; ++i)
    {
        if(fds[i] == -1)
        {
            fds[i] = fd;
            break;
        }
    }
}

void fds_del(int *fds, int fd)
{
    int i = 0;
    for(; i<MAXFD; ++i)
    {
        if(fds[i] == fd)
        {
            fds[i] = -1;
            break;
        }
    }
}

int main()
{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);
    
    struct sockaddr_in saddr,caddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(6000);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    int res = bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
    assert(res != -1);
    
    listen(sockfd, 5);
    
    int fds[MAXFD];
    fds_init(fds);
    
    fds_add(fds,sockfd);
    
    fd_set fdset;
    
    while(1)
    {
        FD_ZERO(&fdset);
        int maxfd = -1;
        int i = 0;
        for(; i<MAXFD; ++i)
        {
            if(fds[i] == -1)
            {
                continue;
            }
            FD_SET(fds[i], &fdset);
            if(maxfd < fds[i])
            {
                maxfd = fds[i];
            }
        }
        
        struct timeval tv = {5,0};

            int n = select(maxfd+1, &fdset, NULL, NULL, &tv);
            if(n == -1)
            {
                perror("select error");
                continue;
            }
            else if( n == 0)
            {
                printf("time out\n");
                continue;
            }
            else
            {
                int i = 0;
                for(; i<MAXFD; ++i)
                {
                    if(fds[i] == -1)
                    {
                        continue;
                    }
                    if(FD_ISSET(fds[i], &fdset))
                    {
                        if(sockfd == fds[i])
                        {
                            int len = sizeof(caddr);
                            int c = accept(sockfd, (struct sockaddr *)&caddr, &len);
                            if(c<0)
                            {
                                continue;
                            }
                            fds_add(fds, c);
                            printf("accept c=%d\n",c);
                        }
                        else
                        {
                            char buff[128] = { 0};
                                int num = recv(fds[i], buff, 127, 0);
                                if(num <= 0)
                                {
                                    printf("client %d is over!\n",fds[i]);
                                    close(fds[i]);
                                    fds_del(fds,fds[i]);
                                }
                                else
                                {
                                    printf("recv(%d)=%s\n",fds[i],buff);
                                    send(fds[i], "ok", 2, 0);
                                }
                        }
                    }
                }
            }
    }
}

                            
