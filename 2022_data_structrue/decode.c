// # include<stdio.h>
// # include<stdlib.h>
// # include<stdint.h>
// # include<windows.h>

// unsigned __int8 * RC4Init(unsigned __int8 *a1, unsigned __int8 *a2, unsigned int a3)
// {
//   unsigned __int8 *result; // eax
//   unsigned __int8 v4; // [esp+0h] [ebp-10h]
//   int v5; // [esp+4h] [ebp-Ch]
//   int v6; // [esp+8h] [ebp-8h]
//   int i; // [esp+Ch] [ebp-4h]

//   for ( i = 0; i <= 255; ++i )
//   {
//     result = &a1[i];
//     a1[i] = i;
//   }
//   v6 = 0;
//   v5 = 0;
//   while ( v6 <= 255 )
//   {
//     v5 = (unsigned __int8)(a1[v6] + v5 + a2[v6 % a3]);
//     v4 = a1[v6];
//     a1[v6] = a1[v5];
//     result = &a1[v5];
//     a1[v5] = v4;
//     ++v6;
//   }
//   return result;
// }

// unsigned int RC4Crypt(unsigned char *a1,unsigned char *a2, unsigned int a3)
// {
//   unsigned int result; // eax
//   unsigned char v4; // [esp+0h] [ebp-14h]
//   unsigned int i; // [esp+4h] [ebp-10h]
//   int v6; // [esp+8h] [ebp-Ch]
//   int v7; // [esp+Ch] [ebp-8h]

//   v7 = 0;
//   v6 = 0;
//   for ( i = 0; ; ++i )
//   {
//     result = i;
//     if ( a3 <= i )
//       break;
//     v7 = (unsigned char)(v7 - 1);
//     v6 = (unsigned char)(a1[v7] + v6);
//     v4 = a1[v7];
//     a1[v7] = a1[v6];
//     a1[v6] = v4;
//     a2[i] ^= a1[(unsigned char)(a1[v7] + a1[v6])] ^ 0xD8;
//   }
//   return result;
// }

// int main(int argc, const char **argv, const char **envp)
// {
//   unsigned int v3; // eax
//   unsigned char v5[256]; // [esp+1Eh] [ebp-132h] BYREF
//   // char Str[50]; // [esp+11Eh] [ebp-32h] BYREF
//   unsigned char ida_chars[] =
// {

//   160, 209, 90, 255, 64, 112, 50, 116, 217, 160, 
//   209, 226, 156, 201, 136, 251
// };
  
//   unsigned char Str[] =
// {
// 225, 187, 158, 206, 128,  67,  80, 147, 178, 243, 
//     0, 182, 240, 163, 174, 189,  97, 163, 170, 134, 
//   247, 172, 126,  87, 110, 100, 165, 198, 155, 207, 
//   182, 171, 229,  96, 185, 107, 235, 133, 162, 123, 
//   190, 189, 142, 193,  79, 238,  68, 
// };
//   RC4Init(v5, ida_chars, 16);
//   v3 = strlen((char*)Str);
//   RC4Crypt(v5, Str, 48);
//   printf("%s",Str);
// }


#include<stdio.h>
#include<string.h>
void RC4Init(unsigned char* RC4Box, unsigned char* key, unsigned int keylen) {
    for (int i = 0; i < 256; i++) {
        RC4Box[i] = i;
    }
    for (int i = 0, j = 0; i < 256; i++) {
        j = (j + RC4Box[i] + key[i % keylen]) & 0xff;
        int tmp = RC4Box[i];
        RC4Box[i] = RC4Box[j];
        RC4Box[j] = tmp;
    }
}

// void RC4Crypt(unsigned char* RC4Box, char* data, unsigned int len) {
//     for (int i = 0, j = 0, k = 0; k < len; k++) {
//         i = (i - 1) & 0xff;
//         j = (j + RC4Box[i]) & 0xff;
//         int tmp = RC4Box[i];
//         RC4Box[i] = RC4Box[j];
//         RC4Box[j] = tmp;
//         data[k] ^= RC4Box[(RC4Box[i] + RC4Box[j]) & 0xff];
//     }
// }

unsigned int __cdecl RC4Crypt(unsigned __int8 *a1, char *a2, unsigned int a3)
{
  unsigned int result; // eax
  unsigned __int8 v4; // [esp+0h] [ebp-10h]
  unsigned int i; // [esp+4h] [ebp-Ch]
  int v6 = 0; // [esp+8h] [ebp-8h]
  int v7 = 0; // [esp+Ch] [ebp-4h]


  for ( i = 0; ; ++i )
  {
    result = i;
    if ( a3 <= i )
      break;
    v7 = (unsigned __int8)(v7 - 1);
    v6 = (unsigned __int8)(a1[v7] + v6);
    v4 = a1[v7];
    a1[v7] = a1[v6];
    a1[v6] = v4;
    a2[i] = ~(a2[i] ^ a1[(unsigned __int8)(a1[v7] + a1[v6])]);
  }
  return result;
}
int main()
{
    unsigned char RC4Box[256];

     unsigned char a[] = {225, 187, 158, 206, 128,  67,  80, 147, 178, 243, 
    0, 182, 240, 163, 174, 189,  97, 163, 170, 134, 
  247, 172, 126,  87, 110, 100, 165, 198, 155, 207, 
  182, 171, 229,  96, 185, 107, 235, 133, 162, 123, 
  190, 189, 142, 193,  79, 238,  68};
    unsigned char key[] = { 160, 209, 90, 255, 64, 112, 50, 116, 217, 160, 
  209, 226, 156, 201, 136, 251};
    RC4Init(RC4Box, key, 16);
    RC4Crypt(RC4Box, a, strlen(a));
    printf("%s\n", a);
    return 0;
}
