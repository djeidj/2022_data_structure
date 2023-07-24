#ifndef BINARYTREE_KIT_H // 由于关于树的操作中有很多栈和队列的操作，我们分成两个文件来实现
#define BINARYTREE_KIT_H

#define Increase_size 10 // 关于树的栈的空间不够的时候，所要增加的空间

typedef int ElemType_BiTree; // ElemType指代树中数据的类型，可以自定义

typedef struct BitNode // 二叉树
{
    ElemType_BiTree data;
    BitNode *lchild, *rchild;
} *BiTree;

typedef BiTree BicsTree; // 以下是孩子兄弟表示法的变量名，由于实际上就是二叉树，所以我们利用typedef和define给变量取另外的名字
typedef BitNode BicsNode;
#define firstchild lchild
#define nextsibling rchild

/*
typedef struct BicsNode
{
    ElemType_BiTree data;
    BicsNode *fistchild,*nextsibling;
} *BicsTree;
*/

typedef struct BiThrNode // 线索二叉树
{
    ElemType_BiTree data;
    BiThrNode *lchild,*rchild;
    bool ltag,rtag;
} *BiThrTree;
// 上面是树结构本身的声明，下面是相关栈和队列的声明



typedef BiTree ElemType_Kit; // ElemType_KIt指跟树有关的栈和队列中的元素的数据类型

typedef struct Stack_Kit
{
    ElemType_Kit *elem;
    int top;
    int StackSize;
};

typedef struct Queue_Kit
{
    ElemType_Kit *elem;
    int front,rear,length,queuesize;
};

void CreatStack(Stack_Kit &S, int size);

void IncreaseStack(Stack_Kit &S);

void DestroyStack(Stack_Kit &S);

bool GetTop(Stack_Kit &S, ElemType_Kit &e);

void PushElem(Stack_Kit &S, ElemType_Kit e);

bool PopElem(Stack_Kit &S, ElemType_Kit &e);

bool IsStackempty(Stack_Kit &S);

void PrintStack(Stack_Kit &S);

// 上面是树结构中有关的栈操作，下面是树结构中有关的队列操作

void CreatQueue(Queue_Kit &Q, int size);

void DestroyQueue(Queue_Kit &Q);

void EnQueue(Queue_Kit &Q, ElemType_Kit e);

bool DeQueue(Queue_Kit &Q, ElemType_Kit &e);

bool IsQueueempty(Queue_Kit &Q);
#endif