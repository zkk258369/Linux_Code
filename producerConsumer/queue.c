#include <stdio.h>
#include <assert.h>
#include "queue.h"

void InitQueue(PQueue pq)
{
	assert(pq != NULL);

	pq->front = 0;
	pq->rear = 0;
}

//rear的后一个是front 则满
static bool IsFull(PQueue pq)
{
	assert(pq != NULL);

	return (pq->rear+1)%SIZE == pq->front;
}

void Show(PQueue pq)
{
	assert(pq != NULL);
	if (IsEmpty(pq))
		return;
	int i = 0;
	for (; (i + 1) % SIZE != pq->front; i++)
	{ 
		printf("%d ", pq->elem[i]);
	}
	printf("\n");
}

//入队
bool Push(PQueue pq,int val)
{
	assert(pq != NULL);

	//判满
	if (IsFull(pq))
		return false;
	
	pq->elem[pq->rear] = val;
	//尾指针加一
	pq->rear = (pq->rear + 1) % SIZE;

	return true;
}

//获取队头元素，但不删除
bool GetTop(PQueue pq, int *rtval)
{
	assert(pq != NULL);
	if (IsEmpty(pq))
	{
		return false;
	}
	else
	{
		*rtval = pq->elem[pq->front];
		return true;
	}
}

//获取队头值，且删除
bool Pop(PQueue pq, int *rtval)
{
	assert(pq != NULL);
	if (IsEmpty(pq))
	{
		return false;
	}
	else
	{
		*rtval = pq->elem[pq->front];
		pq->front = (pq->front + 1) % SIZE;
		return true;
	}
}

//判空
bool IsEmpty(PQueue pq)
{
	return pq->front == pq->rear;
}

void Clear(PQueue pq)
{
	pq->front = pq->rear;
}

void Destroy(PQueue pq)
{
	pq->front = pq->rear;
}