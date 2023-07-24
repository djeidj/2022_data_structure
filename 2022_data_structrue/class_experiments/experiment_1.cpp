#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>

using namespace std;//本文件中针对带头节点的多项式链表进行操作

typedef struct //定义链表元素
{
  double coef; // 系数
  int expn;    // 指数
} ElemType;

typedef struct LNode//定义节点
{
  ElemType data;
  LNode *next;
}*Polynomial;

void CopyPolynomial(Polynomial &La,Polynomial &La_)
{
    LNode *pa=La->next,*pa_=La_;
    while(pa)
    {
        pa_->next=new LNode;
        pa_->next->data.coef=pa->data.coef;
        pa_->next->data.expn=pa->data.expn;
        pa_=pa_->next;
        pa=pa->next;
    }
    pa_->next=NULL;
}

void _sort (Polynomial &L)//将输入的指针所指节点后的所有节点中指数最大的节点放在此输入的指针所在节点后
{
    LNode *p,*q=L->next,*temp=L;
    while(q&&q->next)
    {
        if(q->next->data.expn > temp->next->data.expn)
        {
            temp=q;
        }
        q=q->next;
    }
    if(temp!=L)
    {
        p=temp->next;
        temp->next=temp->next->next;
        p->next=L->next;
        L->next=p;
    }
}

void SortPolynomial(Polynomial &L)//对多项式中每一项按照指数进行排序(利用上面的_sort函数)
{
    LNode *p=L;
    while(p->next)
    {
        _sort(p);
        p=p->next;
    }
}

void PurePolynomial(Polynomial &L)//将多项式直接化成理想形式
{
    SortPolynomial(L);//对输入的多项式化成所要顺序
    if(!L->next||!L->next->next) return;
    LNode *p=L,*q=L->next,*temp;
    while(q->next)//对多项式进行纯化
    {
        if(q->next->data.expn==p->next->data.expn)
        {
            p->next->data.coef+=q->next->data.coef;
            temp=q->next;
            q->next=q->next->next;
            delete temp;
        }
        else
        {
            p->next=q;
            p=p->next;
            q=q->next;
        }
    }
    p=L;
    while(p->next)//消去系数为0的数
    {
        if(fabs(p->next->data.coef)<1e-3)
        {
            temp=p->next;
            p->next=p->next->next;
            delete temp;
        }
        else
        {
            p=p->next;
        }
    }
}

void CreatPolynomial(Polynomial &L)//创建多项式并直接化成理想形式(可以在原有基础上创建)
{
    LNode *p=L;
    int i=1;
    while(1)
    {
        p->next=new LNode;
        printf("input 1 to continue to creat a polynomial,input 0 to cancel\n");
        scanf("%d",&i);
        if(i==0)
        {
            delete p->next;
            p->next=NULL;//这个很重要
            break;
        } 
        printf("input the coefficient\n");
        scanf("%lf",&p->next->data.coef);
        printf("input the frequency\n");
        scanf("%d",&p->next->data.expn);
        p=p->next;
    }
    PurePolynomial(L);
}

void DestroyPolynomial(Polynomial &L)//销毁多项式
{
    LNode *p=L->next,*q;
    while(p)
    {
        q=p;
        p=p->next;
        delete q ;
    }
    L->next=NULL;
}

void PrintPolynomial(Polynomial &L)
{
    LNode *p=L->next;
    while(p)
    {
        if(p==L->next)
        {
            printf("(%.2lf)X^%d ",p->data.coef,p->data.expn);
        }
        else
        {
            printf("+ (%.2lf)X^%d",p->data.coef,p->data.expn);
        }
        p=p->next;
    }
    printf("\n");
}

void AddPolynomial(Polynomial &La,Polynomial &Lb,Polynomial &sum)
{
    Polynomial La_=new LNode,Lb_=new LNode;
    La_->next=NULL;
    Lb_->next=NULL;
    CopyPolynomial(La,La_);
    CopyPolynomial(Lb,Lb_);

    sum=La_;
    LNode *p=sum;
    while(p->next)
    {
        p=p->next;
    }
    p->next=Lb_->next;
    delete Lb_;
    PurePolynomial(sum);
}

void SubtractPolynomial(Polynomial &La,Polynomial &Lb,Polynomial &subtract)
{
    Polynomial La_=new LNode,Lb_=new LNode;
    La_->next=NULL;
    Lb_->next=NULL;
    CopyPolynomial(La,La_);
    CopyPolynomial(Lb,Lb_);

    subtract=La_;
    LNode *p=subtract,*q=Lb_->next;
    while(p->next)
    {
        p=p->next;
    }
    while(q)
    {
        q->data.coef=-q->data.coef;
        q=q->next;
    }
    p->next=Lb_->next;
    delete Lb_ ;
    PurePolynomial(subtract);
}

void MultiplyPolynomial(Polynomial &La,Polynomial &Lb,Polynomial &product)
{
    Polynomial La_=new LNode,Lb_=new LNode;
    La_->next=NULL;
    Lb_->next=NULL;
    CopyPolynomial(La,La_);
    CopyPolynomial(Lb,Lb_);

    Polynomial producttemp=new LNode,temphead=new LNode;
    producttemp->next=NULL;
    temphead->next=NULL;
    
    LNode *p=La_->next,*q=Lb_->next,*temp;
    while(q)
    {
        temp=temphead;
        while(p)
        {
            temp->next=new LNode;
            temp->next->data.coef=p->data.coef*q->data.coef;
            temp->next->data.expn=p->data.expn+q->data.expn;
            p=p->next;
            temp=temp->next;
        }
        temp->next=NULL;
        CopyPolynomial(product,producttemp);
        DestroyPolynomial(product);
        AddPolynomial(producttemp,temphead,product);//由于加法不会让加数删除，所以要引进producttemp对上一个product位置进行保存，方便我们删除
        DestroyPolynomial(producttemp);
        DestroyPolynomial(temphead);
        q=q->next;
        p=La_->next;
    }
    DestroyPolynomial(La_);
    DestroyPolynomial(Lb_);
    PurePolynomial(product);
}

void DividPolynomial(Polynomial &La,Polynomial &Lb,Polynomial &quotiment,Polynomial &remain)//输入两个理想形式的多项式，让La作被除多项式，Lb作除多项式
{
    Polynomial Lb_=new LNode,La_=new LNode,Lbtemphead=new LNode;
    La_->next=NULL;
    Lb_->next=NULL;
    Lbtemphead->next=NULL;
    CopyPolynomial(La,La_);
    CopyPolynomial(Lb,Lb_);

    LNode *quotiment_,*Lbtemp,*pb_=Lb_->next;
    quotiment_=quotiment;
    Lbtemp=Lbtemphead;
    
    while(!(La_->next==NULL)&&La_->next->data.expn>=Lb_->next->data.expn)//!(La_->next==NULL)必须放在前面，不然计算机有可能直接指向NULL->data,会报错
    {
        quotiment_->next=new LNode;
        if(fabs(La_->next->data.coef - Lb_->next->data.coef)<1e-2)
        {
            quotiment_->next->data.coef=1;
        }
        else
        {
            quotiment_->next->data.coef=(La_->next->data.coef)/(Lb_->next->data.coef);
        }
        quotiment_->next->data.expn=(La_->next->data.expn)-(Lb_->next->data.expn);

        while(pb_)
        {
            Lbtemp->next=new LNode;
            Lbtemp->next->data.coef=(pb_->data.coef)*(quotiment_->next->data.coef);
            Lbtemp->next->data.expn=(pb_->data.expn)+(quotiment_->next->data.expn);
            pb_=pb_->next;
            Lbtemp=Lbtemp->next;
        }
        Lbtemp->next=NULL;
        quotiment_=quotiment_->next;
        pb_=Lb_->next;

        SubtractPolynomial(La_,Lbtemphead,remain);
        DestroyPolynomial(Lbtemphead);
        DestroyPolynomial(La_);
        CopyPolynomial(remain,La_);
        DestroyPolynomial(remain);
        Lbtemp=Lbtemphead;
    }
    quotiment_->next=NULL;
    CopyPolynomial(La_,remain);
    DestroyPolynomial(La_);
    DestroyPolynomial(Lb_);
    //PurePolynomial(remain);

}

void IndegralPolynomial(Polynomial &L)//求不定积分
{
    Polynomial L_;
    L_=new LNode;
    LNode *p_=L_,*p=L->next;
    while(p)
    {
        p_->next=new LNode;
        if(p->data.expn==0)
        {
            p_->next->data.coef=p->data.coef;
            p_->next->data.expn=1;
        }
        else if(fabs(p->data.coef - (p->data.expn+1))<1e-4)
        {
            p_->next->data.coef=1;
            p_->next->data.expn=p->data.expn+1;
        }
        else
        {
            p_->next->data.expn=p->data.expn+1;
            p_->next->data.coef=p->data.coef/p_->next->data.expn;
        }
        p_=p_->next;
        p=p->next;
    }
    p_->next=NULL;
    PrintPolynomial(L_);
}

void GcdPolynomial(Polynomial &La,Polynomial &Lb,Polynomial &gcd)//最大公因多项式
{
    Polynomial La_=new LNode,Lb_=new LNode,quotiment=new LNode,remain=new LNode;
    remain->next=NULL;
    La_->next=NULL;
    Lb_->next=NULL;
    quotiment->next=NULL;
    remain->next=NULL;

    if(La->next->data.expn>=Lb->next->data.expn&&La->next!=NULL&&Lb->next!=NULL)//保证下面的除法可以执行
    {
        CopyPolynomial(La,La_);
        CopyPolynomial(Lb,Lb_);
    }
    else
    {
        CopyPolynomial(La,Lb_);
        CopyPolynomial(Lb,La_);
    }

    DividPolynomial(La_,Lb_,quotiment,remain);
    while(!(remain->next==NULL))
    {
        DestroyPolynomial(La_);
        CopyPolynomial(Lb_,La_);
        DestroyPolynomial(Lb_);
        CopyPolynomial(remain,Lb_);
        DestroyPolynomial(remain);
        DestroyPolynomial(quotiment);

        /*PrintPolynomial(La_);
        PrintPolynomial(Lb_);
        system("pause");*/

        DividPolynomial(La_,Lb_,quotiment,remain);
    }
    CopyPolynomial(Lb_,gcd);
}

void LcmPolynomial(Polynomial &La,Polynomial &Lb,Polynomial &lcm)//最小公倍多项式
{
    Polynomial gcd=new LNode,product=new LNode,remain=new LNode;
    gcd->next=NULL;
    product->next=NULL;
    remain->next=NULL;
    GcdPolynomial(La,Lb,gcd);
    MultiplyPolynomial(La,Lb,product);
    DividPolynomial(product,gcd,lcm,remain);
}

void DegralPolynomial(Polynomial &L,float &a,float &b)//从a积分到b
{
    Polynomial L_=new LNode;
    float k=0;
    LNode *p_=L_,*p=L->next;
    while(p)
    {
        p_->next=new LNode;
        if(p->data.expn==0)
        {
            p_->next->data.coef=p->data.coef;
            p_->next->data.expn=1;
        }
        else if(fabs(p->data.coef - (p->data.expn+1))<1e-2)
        {
            p_->next->data.coef=1;
            p_->next->data.expn=p->data.expn+1;
        }
        else
        {
            p_->next->data.expn=p->data.expn+1;
            p_->next->data.coef=p->data.coef/p_->data.expn;
        }
        k=k+(p_->next->data.coef*(pow(b,p_->next->data.expn)-pow(a,p_->next->data.expn)));
        p_=p_->next;
        p=p->next;
    }
    p_->next=NULL;
    printf("form %.2f to %.2f,the result is %.2f\n",a,b,k);
}

int Menu()
{
    int i=0;
    printf("input 0 to creat a polynomial\n");
    printf("input 1 to print a polynomial\n");
    printf("input 2 to delete a polynomial\n");
    printf("input 3 to add 2 polynomials\n");
    printf("input 4 to subtract 2 polynomials\n");
    printf("input 5 to multiply 2 polynomials\n");
    printf("input 6 to divide 2 polynomials\n");
    printf("input 7 to get Indefinite integral of a polynomial\n");
    printf("input 8 to get definite integral of a polynomial\n");
    printf("input 9 to get gcd of 2 polynomials\n");
    printf("input 10 to get lcm of 2 polynomials\n");
    scanf("%d",&i);
    return(i);
}

void Is_empty(Polynomial L[],int k)
{
    int j=0;
    for(int i=0;i<k;i++)
    {
        if(L[i]->next!=NULL)
        {
            printf("the %dth polynomial isn't empty\n",i);
            j++;
        }
    }
    if(j==0)
    {
        printf("the %d polynomials are all empty\n",k);
    }
    printf("\n");
    return;
}

int main()
{
    int i,number,a=0,b=0,k=0;
    float m,n;
    Polynomial L[10];
    for(number=0;number<10;number++)
    {
        L[number]=new LNode;
        L[number]->next=NULL;
    }
    while(1)
    {
        Is_empty(L,10);
        i=Menu();
        switch(i)
        {
            case 0 :
            printf("input the number of the polynomial you want to creat\n");
            scanf("%d",&number);
            CreatPolynomial(L[number]);
            break;

            case 1 :
            printf("input the number of the polynomial you want to print\n");
            scanf("%d",&number);
            PrintPolynomial(L[number]);
            system("pause");
            break;

            case 2 :
            printf("input the number of the polynomial you want to delete\n");
            scanf("%d",&number);
            DestroyPolynomial(L[number]);
            break;

            case 3 :
            printf("input the numbers of the polynomials you want to add\n");
            scanf("%d %d",&a, &b);
            printf("input the number of the polynomial you want to deposite the sum\n");
            scanf("%d",&number);
            AddPolynomial(L[a],L[b],L[number]);
            break;
            
            case 4 :
            printf("input the number of the polynomials you want to subtract\n");
            scanf("%d %d",&a, &b);
            printf("input the number of the polynomial you want to deposite the difference\n");
            scanf("%d",&number);
            SubtractPolynomial(L[a],L[b],L[number]);
            break;

            case 5 :
            printf("input the number of the polynomials you want to multiply\n");
            scanf("%d %d",&a, &b);
            printf("input the number of the polynomial you want to deposite the product\n");
            scanf("%d",&number);
            MultiplyPolynomial(L[a],L[b],L[number]);
            break;

            case 6 :
            printf("input the number of the polynomials you want to divide\n");
            scanf("%d %d",&a, &b);
            printf("input the number of the polynomials you want to deposite the quotiment and remainder\n");
            scanf("%d %d",&number,&k);
            DividPolynomial(L[a],L[b],L[number],L[k]);
            break;

            case 7 :
            printf("input the number of the polynomial you want to get the indefinite integral\n");
            scanf("%d",&number);
            IndegralPolynomial(L[number]);
            system("pause");
            break;

            case 8 :
            printf("input the number of the polynomial you want to get the definite integral\n");
            scanf("%d",&number);
            printf("in put the Integral region\n");
            scanf("%f %f",&m,&n);
            DegralPolynomial(L[number],m,n);
            system("pause");
            break;

            case 9 :
            printf("input the number of the polynomials you want to get the gcd\n");
            scanf("%d %d",&a,&b);
            printf("input the number of the polynomial you want to deposite the gcd\n");
            scanf("%d",&number);
            GcdPolynomial(L[a],L[b],L[number]);
            break;

            case 10 :
            printf("input the number of the polynomials you want to get the lcm\n");
            scanf("%d %d",&a,&b);
            printf("input the number of the polynomial you want to deposite the lcm\n");
            scanf("%d",&number);
            LcmPolynomial(L[a],L[b],L[number]);
            break;

            default :
            printf("error!!!\n");
        }
        system("cls");
    }

}
