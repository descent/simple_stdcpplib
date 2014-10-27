#ifndef STRING_H
#define STRING_H

#include "type.h"

#if 0
// kernel loader part function
void asm_memcpy(u8 *dest, u8 *src, int n);
void asm_seg_memcpy(u8 *dest, u8 *src, int n, u16 fs);
void asm_absolute_memcpy(u8 *dest, u8 *src, int n);
#endif

// prefix s is simple; 32 means in protoected mode
static inline u32 s_strlen(const char *s)
{
  u8 len=0;

  while(*s++)
    ++len;
  return len;
}

static inline char* s_strcpy(char *dest, const char *src)
{
  char *p = dest;
  while(*src)
    *dest++ = *src++;
  *dest='\0';
  return p;
}

static inline int s_strcmp(const char *s1, const char *s2)
{
  s8 res;
  while(1)
    if ((res = *s1 - *s2++) != 0 || !*s1++)
      break;
  return res;
}

static inline int s_memcmp(const char *s1, const char *s2, int n)
{
  if ((s1 == 0) || (s2 == 0)) 
  { /* for robustness */
    return (s1 - s2);
  }

  const char * p1 = (const char *)s1;
  const char * p2 = (const char *)s2;
  int i;
  for (i = 0; i < n; i++,p1++,p2++) 
  {
    if (*p1 != *p2) 
    {
      return (*p1 - *p2);
    }
  }
  return 0;
}

// sign version
static inline char* s32_itoa_s(int n, char* str, int radix)
{
  char digit[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char* p=str;
  char* head=str;
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
    n= -n;
  }
  while(n)
  {
    *p++=digit[n%radix];
    //s32_put_char(*(p-1), (u8*)(0xb8000+80*2));
    n/=radix;
  }
  *p=0;
  #if 1
  for (--p; head < p ; ++head, --p)
  {
    char temp=*head;
    if (*(p-1) != '-')
    {
      *head=*p;
      *p=temp;
    }
  }
  #endif
  return str;
}

// no sign version
static inline u8* s32_itoa(u32 n, u8* str, int radix)
{
  char digit[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  u8* p=str;
  u8* head=str;
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
    n= -n;
  }
  while(n)
  {
    *p++=digit[n%radix];
    //s32_put_char(*(p-1), (u8*)(0xb8000+80*2));
    n/=radix;
  }
  *p=0;
  #if 1
  for (--p; head < p ; ++head, --p)
  {
    char temp=*head;
    if (*(p-1) != '-')
    {
      *head=*p;
      *p=temp;
    }
  }
  #endif
  return str;
}

static inline int s32_sprintf(char *str_buf, const char *fmt, ...)
{
  int i=1;
  char *p = str_buf;

  for (; *fmt ; ++fmt)
  {
    if (*fmt != '%')
    {
      *p++ = *fmt;
      continue;
    }
    ++fmt;
    u8 *arg = (u8 *)(&fmt + i); // nst argument address
    u32 arg_content = *((u32*)arg);

    switch (*fmt)
    {
      case 'd':
      {
        u8 str[12]="";
        s32_itoa(arg_content, str, 10);

        u8 *str_ptr = str;
        while(*str_ptr)
          *p++ = *str_ptr++;
        break;
      }
      case 'x':
      {
        u8 str[12]="";
        s32_itoa(arg_content, str, 16);

        u8 *str_ptr = str;
        while(*str_ptr)
          *p++ = *str_ptr++;
        break;
      }
      case 's':
      {
        char *str_ptr = (char *)arg_content;
        while(*str_ptr)
          *p++ = *str_ptr++;
        break;
      }
      default:
        break;
    }
    ++i; // point to next argument
 
  } // end for (char *p = buf; *fmt ; ++fmt, ++i)
  *p='\0';
  return p-str_buf - 1;
}

static inline int atoi(char *s)
{
  // ref: http://blog.csdn.net/wxhhkhl/article/details/6142289
  int n=0,i;
  for(i=0;s[i]>='0'&&s[i]<='9';i++)
  n=n*10+s[i]-'0';//将字符串转换为整型数字
  return n;
}

static inline bool isdigit(int c)
{
  if ('0' <= c && c <= '9')
    return true;
  else
    return false;
}


#endif
