#include<iostream>
#include"Graph_Kit.h"

void CreatQueue(Queue_Kit &q,int size)
{
    q.elem=new int[size];
    q.front=0;
    q.rear=0;
    q.queuesize=size;
    q.length=0;
}

void InreaseQueue(Queue_Kit &q)
{
    int *a=new int[q.queuesize*2];
    for(int i=0;i<q.length;i++)
    {
        a[i]=q.elem[q.front+i];
    }
    delete []q.elem;
    q.elem=a;
    q.queuesize*=2;
    q.front=0;
    q.rear=q.length;
}

void InQueue(Queue_Kit &q,int w)
{
    if(q.length==q.queuesize)
    {
        InreaseQueue(q);
    }
    q.elem[q.rear]=w;
    q.length+=1;
    q.rear=(q.rear+1)%q.queuesize;
}

bool OutQueue(Queue_Kit &q,int &w)
{
    if(q.length==0)return false;
    w=q.elem[q.front];
    q.front=(q.front+1)%q.queuesize;
    q.length-=1;
    return true;
}