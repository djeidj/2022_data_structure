#include<stdio.h>//链栈
#include<stdlib.h>

typedef int Elemtype;
typedef struct LNode
{
    Elemtype elem;
    LNode *next;
}LNode, *LinkStack;

void CreatStack(LinkStack &S)
{
  //hhhh
}

void DestroyStack(LinkStack &S)
{
  while (S)
  {
    LinkStack p = S;
    S = S->next;
    delete p;
  }
}

bool GetTop(LinkStack S, Elemtype &e)
{
  if (!S) return false;
  e = S->elem;
  return true;
}

void PushElem(LinkStack &S, Elemtype e)
{
  LinkStack p = new LNode;
  p->elem = e;
  p->next = S;
  S = p;
}

bool PopElem(LinkStack &S, Elemtype &e) {
  if (!S) return false;
  LinkStack p = S; S = S->next;
  e = p->elem;
  delete p;
  return true;
}

LinkStack ReverseStack(LinkStack &S)//对不带头结点的单链表进行逆序,递归,最初调用时Ltemp=L 4.16
{
    LNode *p=S,*q=S;
    Elemtype e;

    
}