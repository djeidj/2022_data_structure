#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iostream>

int _swith;                     // 控制输出细节的开关
enum status {idle, busy};
enum identity {nmal, vip};
const int SQQUEUE_INC_SIZE = 10;// 每次给循环队列扩容的容量
const int TIME=60;              // 银行营业时间

typedef struct
{
  identity prity;   // 客户是否是VIP账户
  char *name;       // 客户姓名
  int arrival_time; // 客户到达银行的时间
  int service_time; // 客户办理业务所需时间
  int toelrant_time;// 客户的容忍时间，我们认为每个顾客的忍耐时间都是一样的，这样我们对于队列的操作才显得有意义
  int id;           // 客户在cust[]中的位序
} customer;

typedef struct
{
  status cur_status;  // 窗口当前状态：忙or闲
  int cur_start_time; // 当前状态开始的时间
  int cur_customer;   // 当前服务客户的编号（如果在忙）
} window;

typedef struct
{
    customer *cust;
    int front,rear,length,queuesize;
} SqQueue_cust;

void CreatQueue(SqQueue_cust &q,int qsize)
{
    q.cust=new customer[qsize];
    q.front=0;
    q.rear=0;
    q.length=0;
    q.queuesize=qsize; 
}

void IncreaseQueue(SqQueue_cust &q)
{
    customer *a=new customer[q.queuesize+SQQUEUE_INC_SIZE];
    for(int i=0;i<q.length;i++)
    {
        a[i]=q.cust[(q.front+i) % q.queuesize];
    }
    q.front=0;
    q.rear=q.length;
    q.queuesize+=SQQUEUE_INC_SIZE;
    delete []q.cust;
    q.cust=a;
}

void InQueue(SqQueue_cust &q,customer e)
{
    if(q.length==q.queuesize)
    {
        IncreaseQueue(q);
    }
    q.cust[q.rear]=e;
    q.rear=(q.rear+1)%q.queuesize;
    q.length+=1;
}

bool OutQueue(SqQueue_cust &q,customer &e)
{
    if(q.length==0)
    {
        return false;
    }
    e=q.cust[q.front];
    q.front=(q.front+1)%q.queuesize;
    q.length-=1;
    return true;
}

void Bank_Simulation(int nc,customer* &cust,int nw,window* &win) // nc指顾客的总数，nw指窗口的总数
{
    int c=0,w=0,idw=0,t=0,tlbyw=0;              // c与w作为客人与窗口的编号，served_poon用来统计来到银行的人的总数，用来算顾客的离开率
    int served_poon_vip=0,waiting_time_vip=0;   // poon指population，tlbyw指totalbusywindows
    int served_poon=0,waiting_time=0;           // 指VIP的被接待人数和VIP一共接待人数，用来算平均等待时间
    int depart_poon=0,depart_poon_vip=0;        // 用来统计由于忍不了了而离开的顾客

    SqQueue_cust cq,cq_vip;
    CreatQueue(cq,100);                 // 创建一个队列，认为是来银行但还未办理业务的人就会进队
    CreatQueue(cq_vip,100);             // 创建一个VIP队列，如果是VIP，就进入该队列

    for(int i=0;i<nw;i++)               // 初始化所有柜台，将所有柜台设为空闲
    {
        win[i].cur_status=idle;
        win[i].cur_start_time=0;
        idw++;
    }
   
    //以上为初始的设置，以下将银行系统可以抽象分为两个部分，1.客人来了 2.客人走了 对于每一个t讨论这两种情况

    while(t<TIME||cq.length!=0||cq_vip.length!=0||idw<nw)
    {
        if(t<TIME) // 若是已经到了下班时间，自然不会再接待客人（无论是否是VIP）
        {
            for(c=0;c<nc;c++)
            {
                if((cust[c].arrival_time==t) && (cust[c].prity==vip))
                {
                    InQueue(cq_vip,cust[c]);
                    served_poon_vip++;
                    if(_swith==1)
                    {
                        std::cout<<"The customer whose id is "<<c <<" enters the VIP queue of the bank"<<std::endl;
                    }
                }
                else if((cust[c].arrival_time==t) && (cust[c].prity==nmal))
                {
                    InQueue(cq,cust[c]);
                    served_poon++;
                    if(_swith==1)
                    {
                        std::cout<<"The customer whose id is "<<c <<" enters the nomal queue of the bank"<<std::endl;
                    }
                }
                
            }
        }
        
        for(w=0;w<nw;w++) // 用来判断在柜台办理业务的客人办完业务没有
        {
            if(win[w].cur_status==busy)
            {
                c=win[w].cur_customer;
                if(cust[c].service_time == (t-win[w].cur_start_time))
                {
                    win[w].cur_status=idle;
                    win[w].cur_start_time=t;
                    idw++;
                    if(_swith==1)
                    {
                        std::cout<<"The customer whose id is "<<c <<" completes the bussiness and departs the bank"<<std::endl;
                    }
                }
            }
        }

        for(w=0;w<nw;w++) // 用来判断vip队伍中的是否可以去办理业务了，注意判断cq_vip是否有人排队
        {
            if(win[w].cur_status==idle && cq_vip.length>0)
            {
                customer k_vip;
                OutQueue(cq_vip,k_vip);
                waiting_time_vip+=(t-k_vip.arrival_time);
                win[w].cur_status=busy;
                win[w].cur_start_time=t;
                win[w].cur_customer=k_vip.id;
                idw--;
                if(_swith==1)
                {
                    std::cout<<"The customer whose id is "<<k_vip.id <<" starts to handle business"<<std::endl;
                }
            }
        }            

        for(w=0;w<nw;w++) // 用来判断正在排队的人是否可以去办理业务，注意判断cq是否有人排队
        {   
            if(win[w].cur_status==idle && cq.length>0)
            {
                customer k;
                OutQueue(cq,k);
                waiting_time+=(t-k.arrival_time);
                win[w].cur_status=busy;
                win[w].cur_start_time=t;
                win[w].cur_customer=k.id;
                idw--;
                if(_swith==1)
                {
                    std::cout<<"The customer whose id is "<<k.id <<" starts to handle business"<<std::endl;
                }
            }            
        }

        while ((cq_vip.length!=0) && (cq_vip.cust[cq_vip.front].toelrant_time == (t-cq_vip.cust[cq_vip.front].arrival_time)))
        {
            customer dp_vip;
            OutQueue(cq_vip,dp_vip);
            depart_poon_vip++;
            if(_swith==1)
            {
                std::cout<<"The customer whose id is "<<dp_vip.id <<" can't stand waiting so long and depart"<<std::endl;
            }
        }

        while((cq.length!=0) && (cq.cust[cq.front].toelrant_time == (t-cq.cust[cq.front].arrival_time)))
        {
            customer dp;
            OutQueue(cq,dp);
            depart_poon++;
            if(_swith==1)
            {
                std::cout<<"The customer whose id is "<<dp.id <<" can't stand waiting so long and depart"<<std::endl;
            }
        }
        
        tlbyw=tlbyw+nw-idw;
        t++;

    }

    /*printf("%d\n",tlbyw);
    printf("%d\n",served_poon_vip);*/
    printf("The average waiting time of normal customers is %f\n",((float)waiting_time)/served_poon);
    printf("The nomal customer departure rate is %f\n",((float)depart_poon)/served_poon);
    printf("The average waiting time of vip customers is %f\n",((float)waiting_time_vip)/served_poon_vip);
    printf("The vip customer departure rate is %f\n",(float)depart_poon_vip/served_poon_vip);
    printf("The average window occup is %f\n",((float)tlbyw)/(nw*TIME));    
}

void customer_simulation(int nc,customer* &cust)// 随机产生顾客列表
{
    int i=0,t=0,k=0;
    char str[4]="123";

    k=rand();
    for(i=0;i<nc;i++)
    {
        t=rand();
        cust[i].arrival_time=t%TIME;
        t=rand();
        cust[i].service_time=t%TIME;
        cust[i].id=i;
        cust[i].toelrant_time=k%(TIME/2);
        cust[i].name = str;
        t=rand();
        if(t%5==1)
        {
            cust[i].prity=vip;
        }
        else
        {
            cust[i].prity=nmal;
        }
    }
}

int main()
{
    int nc,nw;
    customer *cust;
    window *win;
    srand((unsigned int) time(NULL));

    std:: cout << "Please input the population of customer" << std:: endl;
    std:: cin >> nc ;
    std:: cout << "Please input the population of windows" << std:: endl;
    std:: cin >> nw ;
    std:: cout << "Please choose whether you want to print the details(1(Yes)/2(No))" << std:: endl;
    std:: cin >> _swith;

    win = new window[nw];//            win=(window *)malloc(sizeof(window)*nw);
    cust = new customer[nc];
      
    customer_simulation(nc,cust);
    Bank_Simulation(nc,cust,nw,win);
}
