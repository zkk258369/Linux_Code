#define _GNU_SOURCE
#include<stdio.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>

#include<poll.h>
#include<sys/types.h>
#define SIZE 100

void init_fds(struct pollfd *fds)
{

    int i = 0;
    for(; i<SIZE; ++i)
    {

        fds[i].fd = -1;
        fds[i].events = 0;
        fds[i].revents = 0;
    }
}

void insert_fd(struct pollfd *fds,int fd,short event)
{

    int i = 0;
    for(; i<SIZE; ++i)
    {

        if(fds[i].fd == -1)
        {

            fds[i].fd = fd;
            fds[i].events = event;
            break;
        }
    }
}

void delete_fd(struct pollfd *fds,int fd)
{

    int i = 0;
    for(; i < SIZE; ++i)
    {

        if(fds[i].fd == fd)
        {

            fds[i].fd = -1;
            fds[i].events = -1;
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
    
    struct pollfd fds[SIZE];
    init_fds(fds);
    insert_fd(fds,sockfd,POLLIN);
    
    while(1)
    {

        int n = poll(fds,SIZE,-1);
        if(n <= 0)
        {

            perror("poll error");
            continue;
        }
        else
        {

            int i = 0;
            for(; i<SIZE; ++i)
            {

                int fd = fds[i].fd;
                if(fd != -1)
                {

                    if(fds[i].revents & POLLRDHUP)
                    {

                        printf("client %d is over!\n",fd);
                        close(fd);
                        delete_fd(fds,fd);
                    }
                    else if(fds[i].revents & POLLIN)
                    {

                        if(fd == sockfd)
                        {

                            int len = sizeof(caddr);
                            int c = accept(fd,(struct sockaddr *)&caddr,&len);
                            if(c < 0)
                            {

                                continue;
                            }
                            insert_fd(fds,c,POLLIN | POLLRDHUP);
                        }
                        else
                        {

                            char buff[128] = {
                                0};
                                recv(fd,buff,127,0);
                                printf("recv(%d):%s",fd,buff);
                                send(fd,"ok",2,0);
                        }
                    }
                }
            }
        }
    }
    
    exit(0);   
}

