// 对一个带有头结点的单链表进行从小到大的插入排序

// 下面给出了数据结构的定义，以及一些辅助函数和测试函数，答题仅需要完成相应的函数
// 编写完成后，可以使用main函数测试

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    LNode* next;
} *LinkList;

// 需要完成的函数
void InsertSort(LinkList &head)
{
    // 可以把链表划分成两个部分，前面的是排好序的，后面的是无序的，
    LinkList head_ = head->next->next,comp,temp;// head_是无序链表， comp表示"compare"指针
    head->next->next=NULL;
    while(head_)
    {
        temp=head_->next;
        comp = head;
        while(comp->next && comp->next->data < head_->data)
        {
            comp = comp->next;
        }
        head_->next = comp->next;
        comp->next = head_;
        head_ = temp;
    }
}

// 下面是一个辅助函数，功能是产生一个长度为N的单链表，表中的数字是随机数
LinkList RandomNumberLinkList(int N) {
    // 先创建一个头结点，头结点不放数据
    LNode* h = new LNode;
    LNode* p = h;
    for (int i = 0; i < N; ++i) {
        // 依次创建N个数据结点
        LNode* t = new LNode;
        t->data = rand() % 1000;
        p->next = t; p = t;
    }
    p->next = NULL;
    return h;
}

// 下面是一个辅助函数，功能是打印一个单链表
void PrintLinkList(LinkList head) {
    // 头结点不放数据，跳过
    LNode* p = head->next;
    while (p) {
        // 依次打印每个数据
        printf("%d", p->data);
        if (p->next) {
            printf("->");
        }
        p = p->next;
    }
}

// 下面是主函数，用于测试
int main() {
    int N = 10;
    LinkList head = RandomNumberLinkList(N);
    InsertSort(head);
    PrintLinkList(head);
    return EXIT_SUCCESS;
}
