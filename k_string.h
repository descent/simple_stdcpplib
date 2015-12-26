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

static inline char* s_strncpy(char *dest, const char *src, int n)
{
  char *p = dest;
  int i=0;
  while(*src)
  {
    *dest++ = *src++;
    ++i;
    if (i >= n)
      break;
  }
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

static inline int atoi(const char *s)
{
  // ref: http://blog.csdn.net/wxhhkhl/article/details/6142289
  int n=0,i;

  if (s[0] == '-')
    i = 1;
  else
    i = 0;

  for(; s[i]>='0' && s[i]<='9';i++)
    n=n*10+s[i]-'0';

  if (s[0] == '-')
    return -n;
  else
    return n;
}

static inline bool isdigit(int c)
{
  if ('0' <= c && c <= '9')
    return true;
  else
    return false;
}

static inline int mypow(int x, int y)
{
  int r=1;
  for (int i=0 ; i < y ; ++i)
    r*=x;
  return r;
}

const int PRECISION = 6;

static inline u8* float_to_str(float num)
{
   int whole_part = num;
   int digit = 0, reminder =0;
   //int log_value = log10(num), 
   int index;
   float wt = 0.0;

   // String containg result
   static u8 str[30];

   //Initilise stirng to zero
   //memset(str, 0 ,20);
   
   //u8 whole_str[20] ;
   s32_itoa(whole_part, str, 10);
#if 0
   //Extract the whole part from float num
   for(int  i = 1 ; i < log_value + 2 ; i++)
   {
       wt  =  mypow(10,i);
       reminder = whole_part  %  wt;
       digit = (reminder - digit) / (wt/10);

       //Store digit in string
       str[index--] = digit + 48;              // ASCII value of digit  = digit + 48
       if (index == -1)
          break;    
   }
#endif
    //index = log_value + 1;
    index = s_strlen((const char*)str);
    str[index] = '.';

   float fraction_part  = num - whole_part;
   float tmp1 = fraction_part,  tmp =0;

#if 0
   cout << "fraction_part: " << fraction_part << endl;
   cout << "num: " << num << endl;
   cout << "whole_part: " << whole_part << endl;
#endif
   //Extract the fraction part from  num
   for( int i= 1; i < PRECISION; i++)
   {
      wt =10; 
      tmp  = tmp1 * wt;
      digit = tmp;
      //cout << "digit: " << digit << endl;
      //cout << "tmp: " << tmp << endl;
      //cout << "tmp1: " << tmp1 << endl;

      //Store digit in string
      str[++index] = digit +48;           // ASCII value of digit  = digit + 48
      tmp1 = tmp - digit;
      if (tmp1 == 0.0)
        break;
   }    
   str[index+1] = 0;

   return str;
}

// from: http://tigcc.ticalc.org/doc/limits.html#LONG_MIN
#define LONG_MIN ((long) 0x80000000L)

// from: http://tigcc.ticalc.org/doc/limits.html#LONG_MAX
#define LONG_MAX 0x7FFFFFFFL

#define ULONG_MAX 0xFFFFFFFFUL

// from : http://www.opensource.apple.com/source/xnu/xnu-1456.1.26/bsd/libkern/strtol.c

static inline int isupper(char c)
{
  return (c >= 'A' && c <= 'Z');
}

static inline int isalpha(char c)
{
  return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
static inline int isspace(char c)
{
  return (c == ' ' || c == '\t' || c == '\n' || c == '\12');
}
/*
 * Convert a string to a long integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
static inline long strtol(const char *nptr, char ** endptr=0, int base=10)
{
	register const char *s = nptr;
	register unsigned long acc;
	register int c;
	register unsigned long cutoff;
	register int neg = 0, any, cutlim;

	/*
	 * Skip white space and pick up leading +/- sign if any.
	 * If base is 0, allow 0x for hex and 0 for octal, else
	 * assume decimal; if base is already 16, allow 0x.
	 */
	do {
		c = *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else if (c == '+')
		c = *s++;
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	} else if ((base == 0 || base == 2) &&
	    c == '0' && (*s == 'b' || *s == 'B')) {
		c = s[1];
		s += 2;
		base = 2;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;

	/*
	 * Compute the cutoff value between legal numbers and illegal
	 * numbers.  That is the largest legal value, divided by the
	 * base.  An input number that is greater than this value, if
	 * followed by a legal input character, is too big.  One that
	 * is equal to this value may be valid or not; the limit
	 * between valid and invalid numbers is then based on the last
	 * digit.  For instance, if the range for longs is
	 * [-2147483648..2147483647] and the input base is 10,
	 * cutoff will be set to 214748364 and cutlim to either
	 * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
	 * a value > 214748364, or equal but the next digit is > 7 (or 8),
	 * the number is too big, and we will return a range error.
	 *
	 * Set any if any `digits' consumed; make it negative to indicate
	 * overflow.
	 */
	cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
	cutlim = cutoff % (unsigned long)base;
	cutoff /= (unsigned long)base;
	for (acc = 0, any = 0;; c = *s++) {
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0 || acc > cutoff || acc == cutoff && c > cutlim)
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0) {
		acc = neg ? LONG_MIN : LONG_MAX;
//		errno = ERANGE;
	} else if (neg)
		acc = -acc;
	if (endptr != 0)
		*endptr = (char *)(any ? s - 1 : nptr);
	return (acc);
}

/*
 * Convert a string to an unsigned long integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
static inline unsigned long strtoul(const char *nptr, char **endptr=0, int base=10)
{
	register const char *s = nptr;
	register unsigned long acc;
	register int c;
	register unsigned long cutoff;
	register int neg = 0, any, cutlim;

	/*
	 * See strtol for comments as to the logic used.
	 */
	do {
		c = *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else if (c == '+')
		c = *s++;
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	} else if ((base == 0 || base == 2) &&
	    c == '0' && (*s == 'b' || *s == 'B')) {
		c = s[1];
		s += 2;
		base = 2;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
	cutlim = (unsigned long)ULONG_MAX % (unsigned long)base;
	for (acc = 0, any = 0;; c = *s++) {
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0 || acc > cutoff || acc == cutoff && c > cutlim)
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0) {
		acc = ULONG_MAX;
//		errno = ERANGE;
	} else if (neg)
		acc = -acc;
	if (endptr != 0)
		*endptr = (char *)(any ? s - 1 : nptr);
	return (acc);
}

#endif
