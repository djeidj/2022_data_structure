#include<stdio.h>//单链表
#include<stdlib.h>

typedef int Elemtype;
typedef struct LNode
{
    Elemtype elem;
    LNode *next;
}LNode, *LinkList;

void CreatLinkList(LinkList &L)//创建单链表
{
    LNode *p=L;
    enum choose{yes,no};
    choose h=yes;
    while(h==yes)
    {
        //由于不知道Elemtype具体类型，所以在此不进行创建
    }

}

void InsertElem_withheadnode(LinkList &L,Elemtype e)//带头节点的非递减单链表插入元素
{
    LNode *p=L;
    LNode *q=new LNode;
    q->elem=e;
    while(p->next&&e>p->next->elem)
    {
        p=p->next;
    }
    q->next=p->next;
    p->next=q;
}

void Insert_withoutheadnode(LinkList &L,Elemtype e)//不带头结点的非递减单链表插入元素
{
    LNode *p=L;
    LNode *q=new LNode;
    q->elem=e;
    if(e<L->elem)
    {
        q->next=L;
        L=q;
    }
    else
    {
        while(p->next&&e>p->next->elem)
        {
            p=p->next;
        }
    }
    q->next=p->next;
    p->next=q;
}

void RearrayLinkList(LinkList &L)//不需要尾指针,分离奇偶
{
    LNode *p=L,*q=L;
    while(q->next)
    {
        q=q->next;
    }//q是尾指针
    LNode *L_=q;//记录下最初尾指针位置
    while(p->next!=L_)
    {
        while(p->next&&p->next->elem%2==1)
        {
            p=p->next;
        }
        if(p->next==L_||p==L_) break;//防止p指针直接到了最初尾指针位置，使while中判断失效
        q->next=p->next;
        p->next=p->next->next;
        q=q->next;
    }

}

LinkList ReverseList(LinkList &L)//对不带头结点的单链表进行逆序,递归
{
    LNode *p;
    if(L->next=NULL)
    {
        return L;
    }
    p=ReverseList(L->next);
    L->next->next=L;
    L->next=NULL;
    return p;
}