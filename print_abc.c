#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>


sem_t sema, semb, semc;

void* printa(void* arg)
{
    while(1)
	{
		sem_wait(&sema);
		write(1,"a",1);
		sem_post(&semb);
		sleep(1);
	}
}

void* printb(void* arg)
{
	while(1)
	{
		sem_wait(&semb);
		write(1,"b",1);
		sem_post(&semc);
	}
}

void* printc(void* arg)
{
	while(1)
	{
		sem_wait(&semc);
		write(1,"c",1);
		sem_post(&sema);
	}
}

int main()
{
	sem_init(&sema, 0, 1);
	sem_init(&semb, 0, 0);
	sem_init(&semc, 0, 0);
	
	pthread_t apid, bpid, cpid;
	pthread_create(&apid, NULL, printa, NULL);
	pthread_create(&bpid, NULL, printb, NULL);
	pthread_create(&cpid, NULL, printc, NULL);
	pthread_join(apid, NULL);
	pthread_join(bpid, NULL);
	pthread_join(cpid, NULL);
	
	sem_destroy(&sema);
	sem_destroy(&semb);
	sem_destroy(&semc);
	
	//exit(0);
}
