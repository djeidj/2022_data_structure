#include<stdio.h>
#include<iostream>

typedef int ElemType;

class Array_2
{
    private:
        
    
    public:
        int row;
        int clos;
        ElemType **base;
        Array_2(int m, int n)
        {
            row = m;
            clos = n;
            ElemType* k = new ElemType[m*n];
            base = new ElemType*[m];         //行主序构成二维数组
            for(int i = 0; i < m; i++)
            {
                base[i] = k + i*n;
            }

            for(int i=0; i<row; i++)
            {
                for(int j=0; j<clos; j++)
                {
                    base[i][j] = 0;
                }
            }
        }

        void printarray()
        {
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<clos; j++)
                {
                    std::cout << base[i][j] << ' ';
                }
                std::cout << std::endl;
            }
        }

};



int main()
{
    Array_2 a(10, 10);
    a.printarray();
}