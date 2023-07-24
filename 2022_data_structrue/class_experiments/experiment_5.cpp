#include<iostream>
#include<stdio.h>

typedef int ElemType;

typedef struct
{
    ElemType *r;
    int len;
} SqTable;

void InitList(SqTable &L, int len)
{
    // 0号单元不用
    L.r = (ElemType*)malloc((len+1)*sizeof(ElemType));
    L.len = len;
}

void CopyList(SqTable L, SqTable &newL)
{
    newL.r = (ElemType*)malloc((L.len+1)*sizeof(ElemType));
    newL.len = L.len;
    memcpy(newL.r, L.r, (L.len+1)*sizeof(ElemType));
}




// 求一个整数的p次方
int intpow(int n, unsigned int p)
{
    int res = 1;
    for (unsigned int i=0; i<p; ++i)
        res *= n;
    return res;
}

// 生成一个随机整数，其取值范围是[0, bound]
int randb(int bound)
{
    int r = 0;
    unsigned int power = 0;
    do
    {
        r *= RAND_MAX;
        r += rand(); ++power;
    } while (intpow(RAND_MAX, power) < bound);
    return r % (bound+1);
}

// 随机打乱一个数组
void RandomShuffleList(SqTable L)
{
    ElemType* array = L.r + 1;
    int n = L.len;
    for (int i=n-1; i>0; --i)
    {
        int j = randb(i); // 0<=j<=i
        ElemType tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}



void ShellSort(SqTable &L) //  希尔排序
{
    int gap,temp;
    int j;
    for(gap = L.len/2; gap > 0; gap = gap/2)
    {
        for(int i = gap+1;  i < L.len; i++)
        {
            temp = L.r[i];
            for(j=i-gap; j>0; j-=gap)
            {
                if(L.r[j] <= temp)
                {
                    break;
                }
                L.r[j+gap] = L.r[j];
            }
            L.r[j+gap] = temp;
        }
    }
}



int Partition(SqTable &L, int low, int high)
{
    L.r[0] = L.r[low];
    while(low < high)
    {
        while(low < high && L.r[high] > L.r[0])
        {
            high--;
        }
        L.r[low] = L.r[high];
        while(low < high && L.r[low] < L.r[0])
        {
            low++;
        }
        L.r[high] =L.r[low];
    }
    L.r[low] = L.r[0];
    return low;
}

void QSort(SqTable &L,int low, int high)
{
    if(low < high)
    {
        int pivotidx = Partition(L, low, high);
        QSort(L, low, pivotidx-1);
        QSort(L, pivotidx+1, high);
    }
}

void QuickSort(SqTable &L) //  快速排序
{
    QSort(L, 1, L.len);
}



void HeapAdjust(SqTable &L, int s, int m)
{
    int i,j=s,temp = L.r[s];
    for(i = 2*s; i <=m; i=i*2)
    {
        if(i < m && L.r[i] < L.r[i+1])
        {
            i+=1;
        }
        if(L.r[i] <= temp)
        {
            break;
        }
        L.r[j] = L.r[i];
        j = i;
    }
    L.r[j] = temp;
}

void HeapSort(SqTable &L) // 堆排序
{
    int temp;
    for(int i=L.len/2; i > 0; i--)
    {
        HeapAdjust(L, i, L.len);
    }

    for(int i=L.len; i>0; i--)
    {
        temp = L.r[i];
        L.r[i] = L.r[1];
        L.r[1] = temp;
        HeapAdjust(L, 1, i-1);
    }
}



void Merge(int* Rs, int* Rt, int s, int m, int t) //  有序表的归并
{
  // 已知Rs[s..m]和Rs[m+1..t]都是有序表，将它们归并存储到Rt[s..t]
    int i,j,k;
    for (i=s, j=m+1, k=s; i<=m && j<=t; ++k)
    {
        if (Rs[i] <= Rs[j]) Rt[k] = Rs[i++];
        else Rt[k] = Rs[j++];
    }
    for (; i<=m; ++i, ++k) Rt[k] = Rs[i];
    for (; j<=t; ++j, ++k) Rt[k] = Rs[j];
}

void MSort(int* Rs, int* Rt, int low, int high)
{
  if (low < high)
  {
    int mid = (low+high)/2;
    MSort(Rs, Rt, low, mid);
    MSort(Rs, Rt, mid+1, high);
    Merge(Rs, Rt, low, mid, high);
    for (int i=low; i<=high; ++i) Rs[i] = Rt[i];
  }
}

void MergeSort(SqTable &L) //  归并排序
{
  int* tmp = new int[L.len+1];
  MSort(L.r, tmp, 1, L.len);
  delete []tmp;
}



void BubbleSort(SqTable &L) //  冒泡排序
{
    for(int i = L.len; i > 0;i--)
    {
        for(int j = 1; j < i;j++)
        {
            if(L.r[j] > L.r[j+1])
            {
                int temp = L.r[j];
                L.r[j] = L.r[j+1];
                L.r[j+1] = temp;
            }
        }
    }
}

int main()
{
    int N = 10000;
    SqTable L;
    InitList(L, N);
    for (int i=1; i<=N; ++i) L.r[i] = i;
    RandomShuffleList(L);
    clock_t begin, end;
    
    // 冒泡排序
    SqTable L1;
    CopyList(L, L1);
    begin = clock(); // 计时器开始
    BubbleSort(L1);
    end = clock(); // 计时器结束
    printf("BubbleSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);
    
    // 快速排序
    SqTable L2;
    CopyList(L, L2);
    begin = clock(); // 计时器开始
    QuickSort(L2);
    end = clock(); // 计时器结束
    printf("QuickSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);
    
    // 希尔排序
    SqTable L3;
    CopyList(L, L3);
    begin = clock(); // 计时器开始
    QuickSort(L3);
    end = clock(); // 计时器结束
    printf("ShellSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);

    // 堆排序
    SqTable L4;
    CopyList(L, L4);
    begin = clock();
    HeapSort(L4);
    end = clock();
    printf("HeapSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);

    // 归并排序
    SqTable L5;
    CopyList(L, L5);
    begin = clock();
    MergeSort(L5);
    end = clock();
    printf("MergeSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);

}
