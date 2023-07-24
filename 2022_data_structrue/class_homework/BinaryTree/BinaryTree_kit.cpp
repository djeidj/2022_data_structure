#include<iostream>
#include"BinaryTree_kit.h"

void CreatStack(Stack_Kit &S, int size)
{
    S.elem=new ElemType_Kit[size];
    S.StackSize=size;
    S.top=-1;
}

void IncreaseStack(Stack_Kit &S)
{
    ElemType_Kit *a;
    a=new ElemType_Kit[S.StackSize+Increase_size];
    for (int i = 0; i < S.top+1; i++)
    {
        a[i]=S.elem[i];
    }
    delete []S.elem;
    S.elem=a;
    S.StackSize=S.StackSize+Increase_size;
}

void DestroyStack(Stack_Kit &S)
{
    S.StackSize=0;
    S.top=-1;
    delete []S.elem;
}

bool GetTop(Stack_Kit &S, ElemType_Kit &e)
{
    if(S.top==-1) return false;
    e=S.elem[S.top];
    return true;
}

void PushElem(Stack_Kit &S, ElemType_Kit e)
{
    if(S.top==S.StackSize-1) IncreaseStack(S);
    S.elem[++S.top]=e;
}

bool PopElem(Stack_Kit &S, ElemType_Kit &e)
{
    if(S.top==-1) return false;
    e=S.elem[S.top--];
    return true;
}

bool IsStackempty(Stack_Kit &S)
{
    if (S.top==-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PrintStack(Stack_Kit &S)
{
    for(int i=0;i<=S.top;i++)
    {
        std::cout<<S.elem[i]->data<<"->";
    }
    std::cout<<std::endl;
}

// 上面是树结构中有关的栈操作，下面是树结构中有关的队列操作

void CreatQueue(Queue_Kit &Q, int size)
{
    Q.elem=new ElemType_Kit[size];
    Q.front=0;
    Q.rear=0;
    Q.length=0;
    Q.queuesize=size;
}

void DestroyQueue(Queue_Kit &Q)
{
    delete []Q.elem;
    Q.front=0;
    Q.rear=0;
    Q.length=0;
    Q.queuesize=0;
}

void EnQueue(Queue_Kit &Q, ElemType_Kit e)
{
    Q.elem[Q.rear]=e;
    Q.rear=(Q.rear+1)%Q.queuesize;
    Q.length++;
}

bool DeQueue(Queue_Kit &Q, ElemType_Kit &e)
{
    if(Q.length==0) return false;
    e=Q.elem[Q.front];
    Q.front=(Q.front+1)%Q.queuesize;
    Q.length--;
    return true;
}

bool IsQueueempty(Queue_Kit &Q)
{
    if (Q.length==0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}