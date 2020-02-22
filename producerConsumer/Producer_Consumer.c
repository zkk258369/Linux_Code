#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<semaphore.h>
#include<pthread.h>
#include <sys/sem.h> 
#include<time.h>
#include"queue.h"

Queue buff;
sem_t s,n,e;
int send = 0;

//void* consumer(void* arg);
void* producer(void* arg)
{
    while(1)
    {
        srand((int)time(NULL) + send++);
        int product = rand()%10+1;
        sem_post(&e);
        sem_post(&s);
        Push(&buff, product);
        printf("Push(%d)\n", product);
        sem_wait(&s);
        sem_wait(&n);
        int second = rand()%3;
        sleep(second);
    }
}

void* consumer(void* arg)
{
    while (1)
    {
        srand((int)time(NULL) + send++);
        sem_post(&n);
        sem_post(&s);
        int tmp;
        Pop(&buff, &tmp);
        printf("Pop(%d)\n", tmp);
        sem_wait(&s);
        sem_wait(&e);
        int second = rand()%3;
        sleep(second);
    }
    
}

void p_create_pthread(pthread_t* pid, int len)
{
    int i = 0;
    for(; i < len; ++i)
    {
        pthread_create(&pid[i], NULL, producer, NULL);
    }
}

void c_create_pthread(pthread_t* pid, int len)
{
    int i = 0;
    for(; i < len; ++i)
    {
        pthread_create(&pid[i], NULL, consumer, NULL);
    }
}

void _pthreadJoin(pthread_t* pid, pthread_t* cid, int plen, int clen)
{
    int i = 0;
    int j = 0;
    for(; i < plen; ++i)
    {
        pthread_join(pid[i], NULL);
    }
    for(; j < clen; ++j)
    {
        pthread_join(cid[j], NULL);
    }
}

int main()
{
    InitQueue(&buff);
    sem_init(&s, 0 , 1);
    sem_init(&n, 0, SIZE-1);
    sem_init(&e, 0 , 0);

    pthread_t pid[3];
    pthread_t cid[2];
    p_create_pthread(pid, 3);
    c_create_pthread(cid, 2);
    while(1)
    {
        sleep(2);
        printf("buff::");
        Show(&buff);
    }
    _pthreadJoin(pid, cid, 3, 2);
    

    sem_destroy(&e);  
    sem_destroy(&n);  
    sem_destroy(&s);

    return 0;
}
