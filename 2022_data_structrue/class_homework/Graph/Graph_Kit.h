#ifndef GRAPH_KIT_H
#define GRAPH_KIT_H

enum GraphKind{DN,DG,UDG,UDN}; // 表示图的类型 DN有向网 DG有向图 UDG无向图 UDN无向网
typedef int VertexType; // 表示顶点的类型
typedef bool ArcType_G; // 表示图弧的类型
typedef int ArcType_N; // 表示网弧的类型

typedef struct
{
    VertexType *Vexs; // 一个记录顶点的数组
    ArcType_G **Arcs; // 一个记录边和权值的邻接矩阵
    int vexnum,arcnum;
    GraphKind kind;
}UDGraph,DGraph;

typedef struct
{
    VertexType *Vexs;
    ArcType_N **Arcs;
    int vexnum,arcnum;
    GraphKind kind;
}UDNet,DNet;
// 上面表示图和网的结构，下面定义辅助数据结构

typedef struct
{
    int *elem;
    int front,rear,length,queuesize;
}Queue_Kit;

void CreatQueue(Queue_Kit &q,int size);

void InreaseQueue(Queue_Kit &q);

void InQueue(Queue_Kit &q,int w);

bool OutQueue(Queue_Kit &q,int &w);
#endif