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

#define MAXEVENTS 100

char* file[] = {
    "main.c", 
    "main.cpp", 
    "main.java", 
    "main.go", 
    "main.py" };

char* build[] = {
    "/usr/local/bin/gcc", 
    "/usr/local/bin/g++", 
    "/usr/bin/javac" };

char* carry[] = {
    "./a.out", 
    "./a.out", 
    "/usr/bin/java" };

char* clidir = "./clidir/";
char* serdir = "./serdir/";

struct Head
{
    int language;
    int file_size;
};
