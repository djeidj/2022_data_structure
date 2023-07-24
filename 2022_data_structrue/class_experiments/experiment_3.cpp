#include<stdio.h>
#include<iostream>
#include<math.h>
#include<string.h>
#include<fstream>

using namespace std;

typedef char ElemType;
typedef unsigned int WeightType;

typedef struct
{
    ElemType data;
    WeightType weight; // 叶子权值的类型
    string code;
    int parent, lchild, rchild; // 三叉静态链表
} HTNode, *HuffmanTree;

typedef struct
{
    ElemType elem;
    WeightType weight;
}ArrayElem;

typedef struct
{
    ArrayElem* array;
    int length;
}array_kit;

typedef struct 
{
    int *elem;
    int top;
}Stack_Kit;

bool IsInArray_Add(array_kit &a,ElemType e) // 判断元素是否在数组中，如果在，权重加1，如果不在，返回false
{
    for(int i=0;i<a.length;i++)
    {
        if(a.array[i].elem==e)
        {
            a.array[i].weight+=1;
            return true;
        }    
    }
    return false;
}

void GetArray(array_kit &a) // 获得stdio.h文件的字符与权重
{
    a.array=new ArrayElem[(int)pow(2, 8)];  
    a.length=0;

    char ch;      
    FILE *fp=fopen("D:\\VScodesample\\2022_data_structrue\\class_experiments\\stdio.h","r");

    while((ch=fgetc(fp))!=EOF) // 不停从文本中读取元素
    {
        if(!IsInArray_Add(a,ch))
        {
            a.array[a.length].elem=ch;
            a.array[a.length].weight=1;
            a.length+=1;
        }
    }
    fclose(fp);
}



void Select(HuffmanTree &HT,int w,int &s1,int &s2) //要求w大于2
{
    int k1 = pow(2,30);
    int k2 = pow(2,30);
    for(int i=0;i<w;i++)
    {
        if(HT[i].parent == -1)
        {
            if(HT[i].weight<k2)
            {
                if(HT[i].weight<k1)
                {
                    k2=k1;
                    k1=HT[i].weight;
                    s2=s1;
                    s1=i;
                }
                else
                {
                    k2=HT[i].weight;
                    s2=i;
                }
            }
        }
    }
}

void CreateHuffmanTree(HuffmanTree &HT,array_kit a)
{
  int m = 2*a.length - 1; // 最终将得到2n-1个结点
  int s1,s2;

  HT = new HTNode[m];

  for (int i=0; i<a.length; ++i)
  {
    HT[i].data = a.array[i].elem;
    HT[i].weight = a.array[i].weight;
    HT[i].lchild = HT[i].rchild = HT[i].parent = -1;
  }

  for (int i = a.length; i<m; ++i)
  {
    Select(HT, i, s1, s2);
    HT[s1].parent = HT[s2].parent = i;
    HT[i].weight = HT[s1].weight + HT[s2].weight;
    HT[i].data = '\0';
    HT[i].lchild = s1;
    HT[i].rchild = s2;
    HT[i].parent = -1;
  }
}



void PrintHuffmanTree1(HuffmanTree HT, int type, int level,int location)
{
    int i;

    if(location == -1) return;

    PrintHuffmanTree1(HT, 2, level+1, (HT+location)->rchild);
    switch (type)
    {
        case 0:
            printf("%c\n", (HT+location)->data);
            break;
        case 1:
            for (i = 0; i < level; i++)
                printf("\t");//
            printf("\\ %c\n", (HT+location)->data);
            break;
        case 2:
            for (i = 0; i < level; i++)
                printf("\t");//
            printf("/ %c\n", (HT+location)->data);
            break;
    }
    PrintHuffmanTree1(HT, 1,  level+1, (HT+location)->lchild);
}

void PrintHuffmanTree(HuffmanTree HT,array_kit a)  // 打印Huffman树
{
    PrintHuffmanTree1(HT, 0, 0, 2*a.length-2);
}


void EncodeHuffman1(HuffmanTree &HT,string coding,int location)
{
    if(location == -1)return;

    string s1,s2;
    s1 = coding+"0";
    s2 = coding+"1";

    (HT+location)->code = coding;
    EncodeHuffman1(HT,s1,(HT+location)->lchild);
    EncodeHuffman1(HT,s2,(HT+location)->rchild);
    
    
}

void EncodeHuffman(HuffmanTree &HT,array_kit a)
{
    EncodeHuffman1(HT, "", 2*a.length-2);
}


void Encode_text(HuffmanTree HT,array_kit a)  // 在此处只是压缩stdio.h文件
{
    string codetxt="";
    char ch;
    unsigned int  n_to_ch=0;

    FILE *fp=fopen("D:\\VScodesample\\2022_data_structrue\\class_experiments\\stdio.h","r");
    FILE *fp_=fopen("D:\\VScodesample\\2022_data_structrue\\class_experiments\\encode.txt","w+");

    while((ch=fgetc(fp))!=EOF)
    {
        for(int i=0;i<a.length;i++)
        {
            if(ch == HT[i].data)
            {
                codetxt+=HT[i].code;
                break;
            }
        }
        while(codetxt.length()>8)
        {
            for(int i=0;i<8;i++)
            {
                fprintf(fp_, "%c", codetxt[i]);
                //n_to_ch+=((int)(ch-'0'))*(int)pow(2,7-i);
            }
            //fprintf(fp_,"%c",(char)n_to_ch);
            //n_to_ch=0;        
            codetxt.erase(0,8);   
        }
    }

    
    for(int i=0;i<codetxt.length();i++)
    {
        fprintf(fp_,"%c",codetxt[i]);
    }       
    codetxt.erase(0,8);
//    cout<<codetxt<<endl<<codetxt_len;
    fclose(fp);
    fclose(fp_);
    cout<<"Encoding is complete"<<endl;

}


void Decode_text(HuffmanTree HT,array_kit a)
{
    char temp;
    int ptr = a.length*2 - 2;

    fstream encode_file;
    encode_file.open("D:\\VScodesample\\2022_data_structrue\\class_experiments\\encode.txt");
    FILE* decode_file=fopen("D:\\VScodesample\\2022_data_structrue\\class_experiments\\decode.txt", "w+");
    while(! encode_file.eof())
    {
        encode_file >> temp;
        if((int)temp == 49)
        {
            ptr = HT[ptr].rchild;
        }
        else if((int)temp == 48)
        {
            ptr = HT[ptr].lchild;
        }
        if(HT[ptr].lchild == HT[ptr].rchild && HT[ptr].lchild == -1 && HT[ptr].rchild == -1)
        {
            fprintf(decode_file, "%c", HT[ptr].data);
            ptr = a.length * 2 - 2;
        }
    }
    cout << "Decode is complete";
    encode_file.close();
    fclose(decode_file);
}

int main()
{
    array_kit a;
    GetArray(a);

    HuffmanTree HT;
    CreateHuffmanTree(HT,a);

    PrintHuffmanTree(HT, a);
    EncodeHuffman(HT,a);
    Encode_text(HT, a);
    Decode_text(HT, a);
}