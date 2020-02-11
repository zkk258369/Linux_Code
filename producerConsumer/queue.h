//#pragma once
//顺序队列，实现成环形队列（出队可以有线性的O(n)变成O(1)）
#include<stdbool.h>
#define SIZE 10
typedef struct Queue
{
	int elem[SIZE];
	int front; // 队头指针，第一个元素的下标
	int rear; //队尾指针,当前可以存放数据的下标
}Queue,*PQueue;

void InitQueue(PQueue pq);

void Show(PQueue pq);

bool Push(PQueue pq,int val);

//获取队头元素，但不删除
bool GetTop(PQueue pq,int *rtval);

//获取队头值，且删除
bool Pop(PQueue pq,int *rtval);

bool IsEmpty(PQueue pq);

void Clear(PQueue pq);

void Destroy(PQueue pq);