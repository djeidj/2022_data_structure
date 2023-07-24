#include <stdio.h>
#include <iostream>

enum color {R, W, B};

void swap(color *a,color *b)
{
    color temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void Sort_RWB(color *a,int len)
{
    int R_high=-1,B_low=len,i=0;
    while(R_high < B_low && i < B_low)
    {
        if(a[i] == R)
        {
            swap(a+i, a+R_high+1);
            R_high++;
            i++;
        }
        else if(a[i] == B)
        {
            swap(a+i, a+B_low-1);
            B_low--;
        }
        else
        {
            i++;
        }
    }
}

void Sort_RWB_1(color *a,int len)
{
    int low,high;

}

int main()
{
    color a[10] = {R, R, W, B, R, R, W, R, B, W};
     for(int i=0; i < 10; i++)
    {
        std::cout<<a[i]<<' ';
    }
    Sort_RWB(a, 10);
    for(int i=0; i < 10; i++)
    {
        std::cout<<a[i]<<' ';
    }
}