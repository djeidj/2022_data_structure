#include<stdio.h>//双向循环链表
#include<stdlib.h>
#include<iostream>

typedef int Elemtype;
typedef struct LNode
{
    LNode *prior;
    Elemtype elem;
    LNode *next;

}LNode, *AdvList;

int AdvListLen(AdvList &L)//带头节点的双向循环链表长度
{
    LNode *p=L->next;
    int i=0;
    while(p!=L)
    {
        i++;
        p=p->next;
    }
    return(i);
}

void RearrayList(AdvList &L)//带头节点的双向循环链表排序
{
    LNode *temp,*p=L->next->next,*q=L;
    while(!(q->next==p)||!(p->next==q)||!(q==p))
    {
        temp=p;
        p=p->next->next;
        temp->prior->next=temp->next;
        temp->next->prior=temp->prior;
        temp->next=q;
        temp->prior=q->prior;
        temp->prior->next=temp;
        temp->next->prior=temp;
        q=temp;
    }
}