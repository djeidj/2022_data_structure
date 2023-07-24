#include <stdio.h>
#include <iostream>
#include "BinaryTree_kit.h"

void PreorderTraverse(BiTree T, void (*visit)(BitNode)) // 先序遍历二叉树（以递归形似），函数指针可以改
{
    if (T)
    {
        visit(*T);
        PreorderTraverse(T->lchild,visit);
        PreorderTraverse(T->rchild,visit);
    }
}
/*
BitNode* PreorderTraverse2(BiTree T, BitNode* (*visit)(BitNode*)) // 只是与PreorderTraverse1的形参不同
{
    if (T)
    {
        BitNode* T_;
        T_=visit(T);
        T_->lchild=PreorderTraverse2(T->lchild,visit);
        T_->rchild=PreorderTraverse2(T->rchild,visit);
    }
    else
    {
        T_=NULL;
    }
    return T_;
}

BitNode* copy(BitNode* T)
{
    BitNode *k=new BitNode;
    k->data=T->data;
    return k;
}
*/

void PreorderTraverse1(BiTree T, void (*visit)(BitNode)) // 先序遍历二叉树（以非递归形式）
{
    Stack_Kit S;
    BiTree p=T;
    int size;

    printf("Please input the space you want creat for the stack/n");
    std::cin>>size;

    CreatStack(S,size);
    while(p||!IsStackempty(S))
    {
        if(p)
        {
            visit(*p);
            PushElem(S,p);
            p=p->lchild;
        }
        else
        {
            PopElem(S,p);
            p=p->rchild;
        }
    }
}

void LayerTraverse(BiTree T, void (*visit)(BitNode)) // 层序遍历二叉树
{
    Queue_Kit Q;
    BiTree p;
    int size;

    printf("Please input the space you want creat for the queue/n");
    std::cin>>size;

    CreatQueue(Q,size);
    if(T) EnQueue(Q,T);
    while (!IsQueueempty(Q))
    {
        DeQueue(Q,p);
        visit(*p);
        if (p->lchild)
        {
            EnQueue(Q,p->lchild);
        }
        if (p->rchild)
        {
            EnQueue(Q,p->rchild);
        }
    }
    
}

int CountNodes(BiTree T) // 计算节点个数
{
    int nl,nr;
    if(T)
    {
        nl=CountNodes(T->lchild);
        nr=CountNodes(T->rchild);
        return(1+nl+nr);
    }
    return(0);
}

void OutPath(BiTree &T,Stack_Kit &S) // 打印每个叶子的路径
{
    if(T)
    {
        PushElem(S,T);
        if(!T->lchild&&!T->rchild)
        {
            PrintStack(S);
        }
        OutPath(T->lchild,S);
        OutPath(T->rchild,S);
        PopElem(S,T);
    }
}

void PrintPath(BiTree &T) // 更好地使用上面的程序，不需要在main函数中使用一个Stack_Kit类型的变量
{
    Stack_Kit S;
    CreatStack(S,10);
    OutPath(T,S);
}



// 以下是关于线索二叉树的处理

void InThreading(BiThrTree &T) // 中序线索化二叉树，设最初所有的ltag和rtag都是0
{
    static BiThrTree pre=NULL;
    if(!T) return;
    InThreading(T->lchild);
    if(!T->lchild)
    {
        T->ltag=true;
        T->lchild=pre;
    }
    if(pre&&!pre->rchild)
    {
        pre->rtag=true;
        pre->rchild=T;
    }
    pre=T;
    InThreading(T->rchild);
}

void PreThreading(BiThrTree &T)
{
    static BiThrTree pre=NULL;
    if(!T) return;
    if(!T->lchild)
    {
        T->ltag=true;
        T->lchild=pre;
    }
    if(pre&&!pre->rchild)
    {
        pre->rtag=true;
        pre->rchild=T;
    }
    pre=T;
    PreThreading(T->lchild);
    PreThreading(T->rchild);
}

//对于所有线索二叉树，只有中序线索二叉树最实用，因为中序线索二叉树可以很方便地找到任何一个节点的中序前驱与中序后继
//对于先序线索二叉树，当ltag==false时，找它的先序前驱很困难，因为要找它的双亲结点
//对于后序线索二叉树，当rtag==false时，找它的后序后继很困难，因为要找它的双亲结点



void PreorderCopy(BiTree T,BiTree &T_) // 6.14 也可以用PreorderTraverse函数，但是形参要改变
{
    if(T)
    {
        T_=new BitNode;
        T_->data=T->data;
        PreorderCopy(T->lchild,T_->lchild);
        PreorderCopy(T->rchild,T_->rchild);
    }
    else
    {
        T_=NULL;
    }
}

bool IsSimilar(BiTree A,BiTree B) // 6.18
{
    if(A==NULL&&B==NULL)
    {
        return true;
    }
    else if(A!=NULL&&B!=NULL)
    {
        bool k;
        k=(IsSimilar(A->lchild,B->lchild)&&IsSimilar(A->rchild,B->rchild));
        return k;
    }
    return false;
}

void K_Value(BiTree T,int k) // 6.26
{
    static int a=0;
    if(T)
    {
        a++;
        if(a==k)
        {
            std::cout<<T->data<<std::endl;
            system("pause");
            exit(0);
        }
        K_Value(T->lchild,k);
        K_Value(T->rchild,k);
    }
}

void Ancestor(BiTree &T,Stack_Kit &S,BitNode* X) // 6.25 X是一个节点的指针
{
    if(T)
    {
        PushElem(S,T);
        if(T==X)
        {
            exit;
        }
        Ancestor(T->lchild,S,X);
        Ancestor(T->rchild,S,X);
        PopElem(S,T);
    }
}

void CommonAncestor(BiTree &T,BitNode* X,BitNode* Y) // 6.25完整程序
{
    Stack_Kit S1,S2;
    int i=0;

    CreatStack(S1,10);
    CreatStack(S2,10); // 创建两个栈，大小为10*sizeof(BitNode*)

    Ancestor(T,S1,X);
    Ancestor(T,S2,Y);

    while(S1.elem[i]==S2.elem[i]) i++;
    std::cout<<S1.elem[i-1]->data<<std::endl;
}

int CountLeaves(BicsTree T) // 6.20
{
    int number=0;
    BicsTree p=T;
    if(T)
    {
        if(T->firstchild==NULL)
        {
            number+=1;
        }
        number+=CountLeaves(T->firstchild);
        number+=CountLeaves(p->nextsibling);
        return number;
    }
    return 0;
}

int CountLeaves1(BicsTree T)
{
    int number = 0;
    if(!T->firstchild) return 1;
    
    BicsTree p;
    for(p = T->firstchild; p; p = p->nextsibling)
    {
        number += CountLeaves1(p);
    }
    return number;
}