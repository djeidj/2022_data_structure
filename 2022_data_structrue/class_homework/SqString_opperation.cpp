#include<stdio.h>//主要是写一个kmp算法
#include<string.h>

void Get_Next(char *p,int *next) // 感觉核心是数学归纳法，知道了next[i],可以求next[i+1];
{
    next[0]=-1;next[1]=0;
    int i=1,j=0;//j=next[i]=next[1]=0
    while (i<strlen(p)-1)//
    {
        if(j==-1||p[i]==p[j])//p[j]在j==-1时，会越界，所以我们先判断j==-1?
        {
            next[i+1]=j+1;//事实上这一句的意思就是p[i]==p[next[i]]时，next[i+1]=next[i]+1，还有一种情况，就是j=-1，但是当j=-1，
            i++;          //而-1=next[0],所以只有当p[i]!=p[j]==p[0]时，我么下一步才有j=next[0]=-1,意思就是p[0]-p[i]前后缀相等长度为0
            j++;          //此时next[i+1]=0
            /*
            可以简化为
            i++;
            j++;
            next[i]=j;
            */
        }
        else
        {
            j=next[j];//这一句的意思就是p[i]!=p[next[i]]时，相当于s[i]!=p[j]，我们让j=next[j],继续比较
        }
    }
    
}

void Get_Next1(char *p, int *next)
{
    next[0]=-1;
    int i=0,j=-1;
    while (i<strlen(p))
    {
        if (j==-1||p[i]==p[j])
        {
            i++;
            j++;
            if(p[i]==p[j]) next[i]=next[j];
            else next[i]=j;
        }
        else
        {
            j=next[j];
        }
    }
}

int Find_kmp(char *s,char *p,int start,int *next)//在串s的start位置开始寻找，找到返回位置，没有就返回-1
{
    if(start<0||start>strlen(s) - strlen(p))
    {
        printf("Wrong!!!!\n");
        return -1;
    }
    int i=start,j=0;
    while(i<strlen(s)&&j<(int)strlen(p))
    {
        if(j==-1||s[i]==p[j])//当前字符相等，则继续下一个
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];//若字符不相等，则按照算法滑动模式
        }
        if(j==strlen(p))return(i-j);
    }
    return -1;
}
