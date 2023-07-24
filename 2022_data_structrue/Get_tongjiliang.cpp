#include<iostream>
#include<math.h>

float Get_junzhi(float *sample, int counter)
{
    float junzhi = 0;
    for(int i=0; i < counter; i++)
    {
        junzhi +=sample[i];
    }
    return junzhi/counter;
}

float Get_fangcha(float *sample, int counter)
{
    float junzhi;
    junzhi = Get_junzhi(sample, counter);

    float fangcha = 0;
    for(int i = 0; i < counter; i++)
    {
        fangcha += pow((sample[i] - junzhi), 2);
    }
    fangcha = fangcha/(counter -1);  

    return fangcha;
}

int main()
{
    float *sample;
    int counter;

    std::cout << "Please input the number:" << std::endl;
    std::cin >> counter;

    sample = new float[counter];

    std::cout << "Please input the sample:" << std::endl;
    for(int i = 0; i < counter; i++)
    {
        std::cin >> sample[i];
    }

    std::cout << "junzhi is: " << Get_junzhi(sample, counter) << std::endl;
    std::cout << "fangcha is: " << Get_fangcha(sample, counter) << std::endl;
}