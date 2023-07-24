#include<stdio.h>//双向循环链表
#include<stdlib.h>
#include<iostream>

typedef int Elemtype;

class LNode
{
    public:
        LNode* prev;
        Elemtype data;
        LNode* next;
        LNode(Elemtype tmpdata)
        {
            prev = nullptr;
            data = tmpdata;
            next = nullptr;
        }
};

class AdvList
{
    private:
        LNode* head;

    public:
        int length;
        AdvList()
        {
            head = nullptr;
            length = 0;
        }

        void insertLNodeathead(Elemtype data)
        {
            LNode* p = new LNode(data);
            if(head == nullptr)
            {
                head = p;
                p->next = p;
                p->prev = p;
            }
            else
            {
                p->next = head->next;
                p->prev = head;
                head->next->prev = p;
                head->next = p;
            }
            length++;
        }

        void insertLNodeattail(Elemtype data)
        {
            LNode* p = new LNode(data);
            if(head == nullptr)
            {
                head = p;
                p->next = p;
                p->prev = p;
            }
            else
            {
                p->next = head;
                p->prev = head->prev;
                head->prev->next = p;
                head->prev = p;                
            }
            length++;
        }

        void printlength()
        {
            std::cout << "The AdvList's length is " << length << std::endl;
        }

        void printAdvList()
        {
            LNode* p = head;
            do
            {
                std::cout << p->data << ' ';
                p = p->next;
            }while(p != head);
            std::cout << std::endl;
        }

};


// void RearrayList(AdvList &L)//带头节点的双向循环链表排序
// {
//     LNode *temp,*p=L->next->next,*q=L;
//     while(!(q->next==p)||!(p->next==q)||!(q==p))
//     {
//         temp=p;
//         p=p->next->next;
//         temp->prior->next=temp->next;
//         temp->next->prior=temp->prior;
//         temp->next=q;
//         temp->prior=q->prior;
//         temp->prior->next=temp;
//         temp->next->prior=temp;
//         q=temp;
//     }
// }
int main()
{
    AdvList L;
    L.insertLNodeathead(0);
    L.insertLNodeattail(1);
    L.insertLNodeattail(2);
    L.printlength();
    L.printAdvList();
    system("pause");
}