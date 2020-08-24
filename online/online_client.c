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

int StartLink(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sockfd)
        return -1;

    struct sockaddr_in cli;
    memset(&cli, 0, sizeof(cli));
    cli.sin_family = AF_INET;
    cli.sin_port = htons(6000);
    cli.sin_addr.s_addr = inet_addr("127.0.0.1");

    int res = connect(sockfd, (struct sockaddr*)&cli, sizeof(cli));
    if(-1 == res)
        return -1;

    return sockfd;
}

int ChoiceLanguage(void)
{
    system("clear");
    printf("******************************\n");
    printf("**** choose a language *******\n");
    printf("******************************\n");
    printf("******************************\n");
    printf("****  1      C语言   *****\n");
    printf("****  2      C++     *****\n");
    printf("****  3      Java    *****\n");
    printf("******************************\n");
    printf("Please input Language(input number): ");
    int language = 0;
    scanf("%d", &language);

    return language;
}

void WriteCode(int flag, int language)
{
    if(2 == flag)
        unlink(file[language-1]);

    pid_t pid = fork();
    assert(pid != -1);
    if(0 == pid)
    {
        //替换成vim
        char filename[50] = {0};
        sprintf(filename, "%.10s%.20s", clidir, file[language-1]);
        execl("/usr/bin/vim", "/usr/bin/vim", filename);
        printf("exec vim error\n");
        exit(0);
    }
    else
    {
        wait(NULL);
    }
}

void SendData(int sockfd, int language)
{
    //1.先发送协议头  language + file_size
    //2.发送代码文件内容

    char filename[50] = {0};
    sprintf(filename, "%.10s%.20s", clidir, file[language-1]);

    struct stat st;
    stat(filename, &st);

    struct Head head;
    head.language = language;
    head.file_size = st.st_size;

    send(sockfd, &head, sizeof(head), 0);

    int fd = open(file[language-1], O_RDONLY);

    while(1)
    {
        char buff[128] = {0};
        int n = read(fd, buff, 127);
        if(n <= 0)
            break;

        send(sockfd, buff, n, 0);
    }
    close(fd);
}

void RecvData(int sockfd)
{
    int size = 0;
    recv(sockfd, &size, 4, 0);

    int num = 0;

    while(1)
    {
        int x = size-num > 127 ? 127 : size-num;
        char buff[128] = {0};
        int n = recv(sockfd, buff, x, 0);
        if(n <= 0)
        {
            close(sockfd);
            exit(0);
        }
        printf("%s", buff);
        num+=n;
        if(num >= size)
            break;
    }
}

int PrintTag()
{
    printf("************************\n");
    printf("** 1 修改代码 **\n");
    printf("** 2 下一个   **\n");
    printf("** 3  退出    **\n");
    printf("************************\n");
    printf("Please input number: ");
    int flag = 0;
    scanf("%d", &flag);

    return flag;
}

int main()
{
    int sockfd = StartLink();
    assert(sockfd != -1);

    int language = ChoiceLanguage();
    int flag = 2;

    while(1)
    {
        //1.用户输入代码
        //2.将选择的语言和代码发送给服务器
        //3.获取服务器端发送的反馈
        //4.给用户提示  1.修改代码  2.编写下一个  3.退出

        //1.
        WriteCode(flag, language);

        //2.
        SendData(sockfd, language);

        //3.
        RecvData(sockfd);

        //4.
        flag = PrintTag();
        if(3 == flag)
            break;
    }

    close(sockfd);
    exit(0);
}

