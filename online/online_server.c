#define _GUN_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include"head.h"

#define MAXEVENTS 100

void DelFinshEvents(int sockfd, int epfd, struct epoll_event events*, int num)
{
    
}

int CreateSocket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sockfd)
        return -1

    struct scokaddr_in ser;
    memset(&ser, 0, sizeof(ser));
    ser.sin_fimily = AF_INET;
    ser.sin_port = htons(6000);
    ser.sin_addr.s_addr = inet

    int res = bind(sockfd, (struct sockaddr*)&ser, sizeof(ser));
    if(-1 == res)
        retutn -1;

    res = listen(sockfd, 5);
    if(-1 == res)
        return -1;

    return sockfd;
}

int main()
{
    int sockfd = CreateSocket();
    assert(-1 != sockfd);

    int epfd = epoll_create(5);
    assert(-1 != epfd);

    struct epoll_evevt event;
    event.data.fd = sockfd;
    event.events = EPOLLIN;

    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);

    while(1)
    {
        struct epoll_event events[MAXEVENTS];
        int n = epoll_wait(epfd, events, MAXEVENTS, -1);
        if(0 >= n)
        {
            printf("epoll_wait error]n");
            continue;
        }

        DelFinshEvents(sockfd, epfd, events, n);
    }
}
