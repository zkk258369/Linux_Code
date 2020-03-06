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
#include<sys/stat.h>
#include"head.h"

#define MAXEVENTS 100

void GetNewConnect(int listenfd, int epfd)
{
    struct sockaddr_in cli;
    socklen_t len = sizeof(cli);
    int connectfd = accept(listenfd, (struct sockaddr*)&cli, &len);
    if(connectfd < 0)
    {
        perror("connectfd error");
        return;
    }
    struct epoll_event event;
    event.data.fd = connectfd;
    event.events = EPOLLIN | EPOLLRDHUP;
    int res = epoll_ctl(epfd, EPOLL_CTL_ADD, connectfd, &event);
    if(res == -1)
        perror("epoll_ctl_add error in GetNewClient()");
}

int RecvCode(int connectfd)
{
    //1.先接受协议头，创建本地文件
    struct Head head;
    recv(connectfd, &head, sizeof(head), 0);
    int filefd = open(file[head.language-1], O_WRONLY | O_TRUNC | O_CREAT, 0664);
    //2.接收代码
    int size = 0;
    while(1)
    {
        int num = head.file_size-size > 127 ? 127 : head.file_size-size;
        char buff[128] = {0};
        int n = recv(connectfd, buff, num, 0);
        if(0 == n)
            break;

        size+=n;
        write(filefd, buff, n);
        if(size >= head.file_size)
            break;
    }
    close(filefd);
    return head.language;
}

int ComplieCode(int language)
{
    struct stat st;
    pid_t pid = fork();
    assert(pid != -1);
    if(pid == 0)
    {
        int fd = open("./complie_error.txt", O_CREAT | O_WRONLY | O_TRUNC, 0664);
        close(1);//关闭标准输出
        close(2);//关闭错误
        dup(fd);
        dup(fd);
        execl(build[language-1], build[language-1], file[language], (char*)0);
        write(fd, "complie error", 13);
        exit(0);
    }
    else
    {
        wait(NULL);
        stat("./build_error.txt", &st);
    }

    return st.st_size;
}

void Execute(int language)
{
    pid_t pid = fork();
    assert(pid != -1);

    if(0 == pid)
    {
        int fd = open("./result.txt", O_WRONLY | O_TRUNC | O_CREAT, 0664);
        close(1);
        close(2);
        dup(fd);
        dup(fd);
        if(language == 3)
        {
            execl(carry[language-1] ,carry[language-1], "main.class", (char*)0);

        }
        else
        {
            execl(carry[language-1] ,carry[language-1], (char*)0);
        }

        write(fd, "execute error", 13);
        exit(0);
    }
    else
    {
        wait(0);
    }
}

void SendResult(int connectfd, int flag)
{
    char* file = "./result.txt";
    if(flag) //如果 flag!=0 则表示编译出错
    {
        file = "./build_error.txt";
    }

    struct stat st;
    stat(file, &st);

    send(connectfd, (int*)&st.st_size, 4, 0);

    int filefd = open(file, O_RDONLY);
    while(1)
    {
        char buff[128] = {0};
        int n = read(filefd, buff, 127);
        if(n <= 0)
            break;
        send(connectfd, buff, n, 0);
    }
    close(filefd);
}

void DealClientData(int connectfd)
{
    //1.接受客户端数据，将代码保存到本都
    //2.编译代码    fork()  exec()
    //3.执行    fork()  exec()
    //4.发送结果

    //1.recv type of language and code file
    int language = RecvCode(connectfd);

    //2.complie code
    int flag = 0;
    flag = ComplieCode(language);
    
    //3.execution
    if(0 == flag)
    {
        Execute(language);
        SendResult(connectfd, flag);
    }
    else
    {
        SendResult(connectfd, flag);
    }
}

void DelFinshEvents(int listenfd, int epfd, struct epoll_event* events, int len)
{
    int i = 0;
    for(; i<len; ++i)
    {
        int sockfd = events[i].data.fd;
        
        //判断是否有新连接
        if(sockfd == listenfd)
        {
            GetNewConnect(sockfd, epfd);
        }
        //连接描述符上有事件产生
        else
        {
            //判断客户端是否关闭
            if(events[i].events & EPOLLRDHUP)
            {
                close(sockfd);
                epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
            }
            //处理其他事件
            else
            {
                DealClientData(sockfd);
            }
        }
    }
}

int CreateSocket()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == listenfd)
        return -1;

    struct sockaddr_in ser;
    memset(&ser, 0, sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_port = htons(6000);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");

    int res = bind(listenfd, (struct sockaddr*)&ser, sizeof(ser));
    if(-1 == res)
        return -1;

    res = listen(listenfd, 5);
    if(-1 == res)
        return -1;

    return listenfd;
}

int main()
{
    int listenfd = CreateSocket();
    assert(-1 != listenfd);

    int epfd = epoll_create(5);
    assert(-1 != epfd);

    struct epoll_event event;
    event.data.fd = listenfd;
    event.events |= EPOLLIN;

    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &event);

    while(1)
    {
        struct epoll_event events[MAXEVENTS];
        int n = epoll_wait(epfd, events, MAXEVENTS, -1);
        if(0 >= n)
        {
            printf("epoll_wait error]n");
            continue;
        }

        DelFinshEvents(listenfd, epfd, events, n);
    }

    exit(0);
}
