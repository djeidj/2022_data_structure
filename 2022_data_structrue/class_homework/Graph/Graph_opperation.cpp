#include<stdio.h>
#include<iostream>
#include"Graph_Kit.h"

void CreatUDG(UDGraph &G)
{
    G.kind=UDG;
    std::cin>>G.vexnum>>G.arcnum;

    int i,j,k;
    ArcType_G *p;
    VertexType vi,vj;

    G.Vexs=new VertexType[G.vexnum]; // 输入顶点数据
    for(i=0;i<G.vexnum;i++)
    {
        std::cin>>G.Vexs[i];
    }

    G.Arcs=new ArcType_G*[G.vexnum]; // 输入邻接矩阵的值,创建的矩阵可能有问题
    for(i=0;i<G.vexnum;i++)
    {
        p=new ArcType_G[G.vexnum];
        G.Arcs[i]=p;
    }
    for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            G.Arcs[i][j]=false;
        }
    }
    for(k=0;k<G.arcnum;k++)
    {
        std::cin>>vi>>vj;
        for(i=0;i<G.vexnum;i++)
        {
            if(G.Vexs[i]==vi)break;
        }
        for(j=0;j<G.vexnum;j++)
        {
            if(G.Vexs[j]==vj)break;
        }
        G.Arcs[i][j]=true;
        G.Arcs[j][i]=true;
    }
}

void CreatUDN(UDNet &N)
{
    N.kind=UDN;
    std::cin>>N.vexnum>>N.arcnum;

    int i,j,k;
    ArcType_N *p,w;
    VertexType vi,vj;

    N.Vexs=new VertexType[N.vexnum]; // 输入顶点数据
    for(i=0;i<N.vexnum;i++)
    {
        std::cin>>N.Vexs[i];
    }

    N.Arcs=new ArcType_N*[N.vexnum]; // 输入邻接矩阵的数据，创建的矩阵可能有问题
    for(i=0;i<N.vexnum;i++)
    {
        p=new ArcType_N[N.vexnum];
        N.Arcs[i]=p;
    }
    for(i=0;i<N.vexnum;i++)
    {
        for(j=0;j<N.vexnum;j++)
        {
            N.Arcs[i][j]=0;
        }
    }
    for(k=0;k<N.arcnum;k++)
    {
        std::cin>>vi>>vj>>w;
        for(i=0;i<N.vexnum;i++)
        {
            if(N.Vexs[i]==vi)break;
        }
        for(j=0;j<N.vexnum;j++)
        {
            if(N.Vexs[j]==vj)break;
        }
        N.Arcs[i][j]=w;
        N.Arcs[j][i]=w;
    }
}

int AdjVex_UDG(UDGraph G,int v,int w=-1) // 获得与一个顶点相连的一个元素
{
    for (int j=w+1;j<G.vexnum;j++)
    {
        if(G.Arcs[v][j]==true)return j;
    }
    return -1;
}

int AdjVex_UDN(UDNet N,int v,int w=-1) // 获得与一个顶点相连的一个元素
{
    for(int j=w+1;j<N.vexnum;j++)
    {
        if(N.Arcs[v][j]!=0)return j;
    }
    return -1;
}

void DFS_UDG(UDGraph &G,int v,bool* Visited,void* visit(UDGraph,int))
{
    visit(G,v);Visited[v]=true;
    for(int w=AdjVex_UDG(G,v);w!=-1;w=AdjVex_UDG(G,v,w))
    {
        if(Visited[w]!=true)
        {
            DFS_UDG(G,w,Visited,visit);
        }
    }
}

void DFSTreverse_UDG(UDGraph &G,int v,void* visit(UDGraph,int))
{
    bool Visited[G.vexnum];
    for(int i=0;i<G.vexnum;i++)
    {
        Visited[i]=false;
    }
    for(int j=0;j<G.vexnum;j++)
    {
        if(Visited[j]!=true)
        {
            DFS_UDG(G,j,Visited,visit);
        }
    }
}

void BFS_UDG(UDGraph &G,Queue_Kit &q,int v,bool* Visited,void* visit(UDGraph,int))
{
    visit(G,v);Visited[v]=true;
    InQueue(q,v);
    while(OutQueue(q,v))                        //  注意一定要操作，再进队，如果出队后操作，会重复进队（这一点与树的层序不同，即图中队列放的是已经操作过的）
    {                                           //  但其实树中层序遍历也可以先操作再进队，但是可能在操作函数上要判定为空的情况
        for(int w=AdjVex_UDG(G,v);w!=-1;w=AdjVex_UDG(G,v,w))
        {
            if(Visited[w]!=true)
            {
                visit(G,w);
                Visited[w]=true;
                InQueue(q,w);
            }
        }
    }  
}

void BFSTreverse_UDG(UDGraph &G,int v,void* visit(UDGraph,int))
{
    Queue_Kit q;
    bool Visited[G.vexnum];

    CreatQueue(q,10);
    for(int i=0;i<G.vexnum;i++)
    {
        Visited[i]=false;
    }

    for(int i=0;i<G.vexnum;i++)
    {
        if(Visited[i]!=true)
        {
            BFS_UDG(G,q,i,Visited,visit);
        }
    }
}

