#ifndef K_STRING_H
#define K_STRING_H

#include "k_string.h"
#include "k_stdio.h"

char* my_itoa_s(long n, char* str, u16 str_len, u8 radix)
{
#ifdef DEBUG_STR_LEN
  DS::myprint("str_len: ");
  DS::myprint((int)str_len);
  DS::myprint("\n");
#endif

  char digit[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char* p=str;
  char* head=str;
  u16 i=0;
  //int radix = 10;

//  if(!p || radix < 2 || radix > 36)
//    return p;
  if (n==0)
  {
    *p++='0';
    *p=0;
    return str;
  }
  if (radix == 10 && n < 0)
  {
    *p++='-';
    ++head;
    ++i;
    n= -n;
  }
  while(i < str_len-1 && n)
  {
    ++i;
    *p++=digit[n%radix];
    //s32_put_char(*(p-1), (u8*)(0xb8000+80*2));
    n/=radix;
  }
  *p=0;

  for (--p; head < p ; ++head, --p)
  {
    char temp=*head;
    {
      *head=*p;
      *p=temp;
    }
  }
  return str;
}

char* my_itoa(unsigned long n, char* str, u16 str_len, u8 radix)
{
#ifdef DEBUG_STR_LEN
  DS::myprint("str_len: ");
  DS::myprint((int)str_len);
  DS::myprint("\n");
#endif
  
  char digit[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char* p=str;
  char* head=str;
  u16 i=0;
  //int radix = 10;

//  if(!p || radix < 2 || radix > 36)
//    return p;
  if (n==0)
  {
    *p++='0';
    *p=0;
    return str;
  }
  while(i < str_len-1 && n)
  {
    ++i;
    *p++=digit[n%radix];
    //s32_put_char(*(p-1), (u8*)(0xb8000+80*2));
    n/=radix;
  }
  *p=0;
  #if 1
  for (--p; head < p ; ++head, --p)
  {
    char temp=*head;
    {
      *head=*p;
      *p=temp;
    }
  }
  #endif
  return str;
}

#endif
