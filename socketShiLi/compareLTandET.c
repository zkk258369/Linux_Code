#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<pthread.h>
#include <stdbool.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

/*将文件描述符设置成非阻塞的*/
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

/*将文件据述符fd上的EPOLLIN注册到epo11fd指示的epol1内核事件表中，参数enableet指定是否对fd启用ET模式*/
void addfd(int epollfd,int fd, bool enable_et)
{
    struct epoll_event event;
    event.data.fd=fd;
    event.events=EPOLLIN;
    if(enable_et)
        event.events |= EPOLLET;
    
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

void LT(struct epoll_event* events, int number, int epfd, int listenfd)
{
    char buff[BUFFER_SIZE];
    int i = 0;
    for(; i < number; ++i)
    {
        int sockfd = events[i].data.fd;
        if(sockfd == listenfd)
        {
            struct sockaddr_in cli;
            int len = sizeof(cli);
            int connectfd = accept(listenfd, (struct sockaddr*)&cli, &len);
            addfd(epfd, connectfd, false);
        }
        else if(events[i].events & EPOLLIN)
        {
            /*只要sockfd读缓存中还有未读出的数据，这段代码就被触发*/
            printf("event trigger once\n");
            memset(buff, '\0', BUFFER_SIZE);
            int ret = recv(sockfd, buff, BUFFER_SIZE-1, 0);
            if(ret <= 0)
            {
                close(sockfd);
                continue;
            }
            printf("get %d bytes of content:%s\n", ret, buff);
        }
        else
        {
            printf("something else happend\n");
        }
    }//end for
}

void ET(struct epoll_event* events, int number, int epfd, int listenfd)
{
    int buff[BUFFER_SIZE];
    int i = 0;
    for(; i<number; ++i)
    {
        int sockfd = events[i].data.fd;
        if(sockfd == listenfd)
        {
            struct sockaddr_in cli;
            int len = sizeof(cli);
            int connectfd = accept(listenfd, (struct sockaddr*)&cli, &len);
            addfd(epfd, connectfd, true);
        }
        else if(events[i].events & EPOLLIN)
        {
            printf("event trigger once\n");
           while(1)
           {
               memset(buff, 0, BUFFER_SIZE);
               int ret = recv(sockfd, buff, BUFFER_SIZE-1, 0);
               if(ret < 0)
               {
                   /*对于非阻塞IO，下面的条件成立表示数据已经全部读取完毕。此后，epo11就能再次触发sockfd上的EPOLLIN事件，以驱动下一次读操作*/
                    if((errno == EAGAIN) || (errno == EWOULDBLOCK))
                    {
                        printf("read later\n");
                        break;
                    }
                    close(sockfd);
                    break;
               }
                else if(ret == 0)
                {
                    close(sockfd);
                }
                else
                {
                    printf("get %d byte of content:%s\n", ret, buff);
                }
           }
        }
        else
        {
            printf("something else happend\n");
        }
        
    }//end for
}

int main(int argc, char* argv[])
{
    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address) );
    address.sin_family = AF_INET;
    address.sin_port = htons(6000);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 5);
    assert(ret != -1);

    struct epoll_event events[MAX_EVENT_NUMBER];
    int epfd = epoll_create(5);
    assert(epfd != -1);

    addfd(epfd, listenfd, true);

    while(1)
    {
        int res = epoll_wait(epfd, events, MAX_EVENT_NUMBER, -1);
        if(res < 0)
        {
            perror("epoll error");
            break;
        }
        //LT(events, res, epfd, listenfd);
        ET(events, res, epfd, listenfd);
    }

    close(listenfd);
    exit(0);
}

