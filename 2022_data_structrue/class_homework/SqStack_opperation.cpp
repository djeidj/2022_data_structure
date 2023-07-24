#include<stdio.h>//顺序栈

typedef char ElemType;
const int SQSTACK_INC_SIZE = 10;

typedef struct 
{
  ElemType *elem; // 基地址
  int stacksize;  // 当前分配内存大小，单位是sizeof(ElemType)
  int top;        // 栈顶位置，定义为表长-1
} SqStack;

void CreatStack(SqStack &S, int msize)
{
  S.elem = new ElemType[msize];
  S.stacksize = msize;
  S.top = -1;
}

void DestroyStack(SqStack &S)
{
  delete []S.elem;
  S.stacksize = 0;
  S.top = -1;
}

bool GetTop(SqStack S, ElemType &e)
{
  if (S.top == -1) return false;
  e = S.elem[S.top];
  return true;
}

void Increment(SqStack &S, int inc_size = SQSTACK_INC_SIZE)
{
  ElemType *a = new ElemType[S.stacksize + inc_size];
  for (int i=0; i<=S.top; ++i) a[i] = S.elem[i];
  delete []S.elem; S.elem = a;
  S.stacksize += inc_size;
}

void PushElem(SqStack &S, ElemType e)
{
  if (S.top == S.stacksize-1) Increment(S);
  S.elem[++S.top] = e;
}

bool PopElem(SqStack &S, ElemType &e)
{
  if (S.top == -1) return false;
  e = S.elem[S.top--];
  return true;
}

bool Is_String(char *str)//4.6
{
    int i=0;
    char e;
    SqStack S;
    CreatStack(S,10);
    while(str[i]!='@')
    {
        PushElem(S,str[i]);
        i++;
    }
    i++;
    while(str[i]!='\0')
    {
        PopElem(S, e);
        if(e!=str[i])
        {
            printf("This is not @ string");
        }
        i++;
    }
    if(S.top!=-1)
    {
        printf("This is not @ string");
    }
    else
    {
        printf("This is @ string");
    }
}