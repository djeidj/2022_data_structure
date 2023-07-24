#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int main()
{
   char a,b;
   
   fstream encode_file,decode_file;
   encode_file.open("D:\\VScodesample\\2022_data_structrue\\class_experiments\\encode.txt");
   //decode_file.open("D:\\VScodesample\\2022_data_structrue\\class_experiments\\decode.txt", ios::noreplace);
   encode_file >> a >> b;
   if((int)a == 49) cout << '1' << endl;

   cout << a << b;
   encode_file.close();
}