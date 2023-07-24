#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>

const int MAX_VERTEX_NUM=30;
const int INFINITY=0x7fffff;

using namespace std;

typedef int ArcType;

typedef struct
{
    int* City_id;
    string* City_name;
    ArcType **City_distance;
    int Vexnum;
}RailwayGraph;

void Creat_Map(RailwayGraph &Map) //  建立铁路网并初始化
{         //  对铁路网初始化
    Map.Vexnum=0;
    Map.City_id = new int[MAX_VERTEX_NUM];
    Map.City_name = new string[MAX_VERTEX_NUM];
    for(int i=0;i<MAX_VERTEX_NUM;i++) //  这个循环成功
    {
        Map.City_id[i] = -1;
        Map.City_name[i] = "";
        //std::cout<<i<<std::endl;
    }

    int *k = new ArcType[MAX_VERTEX_NUM * MAX_VERTEX_NUM];
    Map.City_distance = new ArcType*[MAX_VERTEX_NUM];
    for(int i=0;i<MAX_VERTEX_NUM;i++) //  这个循环成功
    {
        Map.City_distance[i] = k + i * MAX_VERTEX_NUM;
        for(int j=0;j<MAX_VERTEX_NUM;j++)
        {
            Map.City_distance[i][j] = INFINITY;
        }
    }
}

void Getinfo_City(RailwayGraph &Map)
{
    Map.Vexnum = 0;
    int i = 0;

    ifstream info_City;
    info_City.open("D:\\VScodesample\\2022_data_structrue\\class_experiments\\city.txt");
    for(i = 0; i < 25; i++)
    {
        info_City >> Map.City_id[i] >> Map.City_name[i];
        Map.Vexnum++;
    }
    info_City.close();

    ifstream info_Dist;
    int x,y;
    info_Dist.open("D:\\VScodesample\\2022_data_structrue\\class_experiments\\dist.txt");
    while(info_Dist)               //  这一步事实上是一种特殊情况，只有城市数组的索引和城市编号相等才能这么使用
    {
        info_Dist >> x >> y;
        info_Dist >> Map.City_distance[x][y];
        Map.City_distance[y][x] = Map.City_distance[x][y];
        x = 0; y = 0;
    }
    info_Dist.close();

}




void Dijkstra(RailwayGraph Map, int v0,int D[MAX_VERTEX_NUM],int P[][MAX_VERTEX_NUM])
{
    int S[Map.Vexnum] = {0};                      //  用来记录是否已经求出最短路径
    S[v0] = 1;

    for(int i=0; i<Map.Vexnum; i++)
    {
        D[i] = Map.City_distance[v0][i];
        if(D[i] != INFINITY)
        {
            P[i][0] = v0;
            P[i][1] = i;
            P[i][2] = -1;
        }
        else if (i == v0)
        {
            P[i][0] = v0;
            P[i][1] = -1;
        }
        
    }
    D[v0] = 0;

    for(int counter=0; counter<Map.Vexnum; counter++)
    {
        int min = INFINITY,k = v0;
        for(int j = 0; j<Map.Vexnum; j++)
        {
            if((S[j] == 0)&&(min > D[j]))
            {
                min = D[j];
                k = j;
            }
        }

        S[k] = 1;                                                   //  修改S[]数组
        for(int i=0; i<Map.Vexnum; i++)                              
        {
            if((S[i]==0)&&(D[k]+Map.City_distance[k][i] < D[i]))    
            {
                D[i] = D[k]+Map.City_distance[k][i];                //  修改D[]数组
                int j;
                for(j = 0; P[k][j] !=-1; j++)                       //  修改P[][]数组
                {
                    P[i][j] = P[k][j];
                }
                P[i][j] = i;
                P[i][j+1] = -1;
            }
        }

    }

}

void Get_shortestway(RailwayGraph Map,string sour,string dest)
{
   
    int v0,v1;
    for(int i=0; i<Map.Vexnum; i++)
    {
        if(Map.City_name[i] == sour)
        {
            v0 = i; //Map.City_id[i];
        }
        if(Map.City_name[i] == dest)
        {
            v1 = i; //Map.City_id[i];
        }
    }

    int D[Map.Vexnum];
    int P[Map.Vexnum][MAX_VERTEX_NUM];
    Dijkstra(Map, v0, D, P);
    if(D[v1] == INFINITY)
    {
        cout << "can't reach the destination";
    }
    else
    {
        cout << "distance is: " << D[v1] <<endl;
    }
    
    for(int i=0; P[v1][i] !=-1; i++)
    {
        cout << Map.City_name[P[v1][i]] << ' ';
    }
}



void Del_Map(RailwayGraph &Map,string delplace)
{
    int del_id;

    for(int i=0; i<Map.Vexnum; i++)
    {
        if(Map.City_name[i] == delplace)
        {
            del_id = i;
            for(int j = del_id; j<Map.Vexnum-1; j++)
            {
                Map.City_name[j] = Map.City_name[j+1];
                Map.City_id[j] = Map.City_id[j+1];
            }
            Map.City_name[Map.Vexnum-1] = "";
            Map.City_id[Map.Vexnum-1] = -1;
            break;
        }
    }



    for(int i=0; i<Map.Vexnum;i++)
    {
        for(int j=del_id; j<Map.Vexnum-1; j++)
        {
            Map.City_distance[i][j] = Map.City_distance[i][j+1];
        }
        Map.City_distance[i][Map.Vexnum-1] = INFINITY; 
    }
    for(int j=0; j<Map.Vexnum; j++)
    {
        for(int i=del_id; i<Map.Vexnum-1; i++)
        {
            Map.City_distance[i][j] = Map.City_distance[i+1][j];
        }
        Map.City_distance[Map.Vexnum-1][j] = INFINITY; 
    }

    Map.Vexnum--;
}

int main()
{
    RailwayGraph Map;
    Creat_Map(Map);
    Getinfo_City(Map);

    string sour, dest, delplace;

    /**/cout << "please input the source place:" << endl;
    cin >> sour;
    cout << "please input the destination palce" << endl;
    cin >> dest;
    
    Get_shortestway(Map, sour, dest);
    system("pause");
    system("cls");

    cout << "please input the place you want to delete from the map ";
    cin >> delplace;

    Del_Map(Map, delplace);

    cout << "please input the source place:" << endl;
    cin >> sour;
    cout << "please input the destination palce" << endl;
    cin >> dest;

    Get_shortestway(Map, sour, dest);

    /*for(int i = 0; i <Map.Vexnum; i++)
    {
        cout << i << ' ' << Map.City_id[i] << Map.City_name[i] << endl;
    }
    cout <<endl;
    for(int i = 0; i < Map.Vexnum; i++)
    {
        for(int j = 0; j < Map.Vexnum; j++)
        {
            if(Map.City_distance[i][j] == INFINITY)
            {
                cout << -1 << ' ';
            }
            else
            {
                cout << Map.City_distance[i][j] << ' ';
            }
            
        }
        cout << endl;
    }*/
}