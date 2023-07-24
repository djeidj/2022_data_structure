#include<stdio.h>//顺序表
#include<stdlib.h>

typedef int Elemtype;

struct Sqlist
{
    Elemtype *head;
    int Listsize;
    int Listlength;
};

void CreatList(Sqlist &L,int Spacesize)
{
    L.head=(Elemtype*)malloc(100*sizeof(Elemtype));
    L.Listlength=0;
    L.Listsize=Spacesize;
}

void ExtendList(Sqlist &L)//扩展20个sizeof（Elemtype）
{
    L.head=(Elemtype *)realloc(L.head,L.Listsize+20);
    L.Listsize=L.Listsize+20;
}

void InsertElem(Sqlist &L,Elemtype e)//L是非递减有序数列
{
    int i=0,j=0;
    if(L.Listlength==L.Listsize) ExtendList(L);
    while (e>L.head[i]) i++;
    while(L.Listlength-1-j>=i)
    {
        L.head[L.Listlength-j]=L.head[L.Listlength-1-j];
        j++;
    }
    L.head[i]=e;
    L.Listlength++;
}

void ReverseList(Sqlist &L)//倒置顺序表
{
    Elemtype temp;
    for(int i=0;i<=((L.Listlength/2)-1);i++)
    {
        temp=L.head[i];
        L.head[i]=L.head[L.Listlength-1-i];
        L.head[L.Listlength-1-i]=temp;
    }
}

void RearraySqList(Sqlist &L)//Elem是整数，要求奇数放在左边，偶数放在右边
{
    int i=0,j=0,temp;
    while(i<L.Listlength-1-j)
    {
        while(L.head[i]%2==1) i++;
        while(L.head[L.Listlength-1-j]%2==0) j++;
        if(i>L.Listlength-1-j) break;
        temp=L.head[i];
        L.head[i]=L.head[L.Listlength-1-j];
        L.head[L.Listlength-1-j]=temp;
    }
}//这个算法自我感觉很好