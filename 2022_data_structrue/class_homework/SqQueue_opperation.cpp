#include<stdio.h>//顺序队列
#include<stdlib.h>

typedef char ElemType;
const int SQQUEUE_INC_SIZE = 10;

typedef struct
{
    ElemType *elem;
    int front,rear,length,queuesize;
} SqQueue;

void CreatQueue(SqQueue &q,int size)
{
    q.elem=new ElemType[size];
    q.front=q.rear=q.length=0;
    q.queuesize=size;
}

void IncreaseQueue(SqQueue &q)//由于是循环队列，所以要注意一下
{
    ElemType *a=new ElemType[q.queuesize+SQQUEUE_INC_SIZE];
    for(int i=0;i<q.length;i++)
    {
        a[i]=q.elem[(q.front+i) % q.queuesize];
    }
    delete []q.elem;
    q.elem=a;
    q.queuesize+=SQQUEUE_INC_SIZE;
    q.front=0;
    q.rear=q.length;
}

void InQueue(SqQueue &q,ElemType e)
{
    if(q.length==q.queuesize)
    {
        IncreaseQueue(q);
    }
    q.elem[q.rear]=e;
    q.rear=(q.rear+1) % q.queuesize;
    q.length+=1;
}

bool OutQueue(SqQueue &q,ElemType &e)
{
    if(q.length==0) return false;
    e=q.elem[q.front];
    q.front=(q.front+1)%q.queuesize;
    q.length-=1;
}

