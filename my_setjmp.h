/*
 * Copyright (C) 1991 DJ Delorie

#ifdef X86_16
  __asm__(".code16gcc\n");
#endif
 * All rights reserved.
 *
 * Redistribution, modification, and use in source and binary forms is permitted
 * provided that the above copyright notice and following paragraph are
 * duplicated in all such forms.
 *
 * This file is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* Modified to use SETJMP_DJ_H rather than SETJMP_H to avoid
   conflicting with setjmp.h.  Ian Taylor, Cygnus support, April,
   1993.  */

#ifndef MY_SETJMP_H
#define MY_SETJMP_H


// #define UEFI
#ifdef UEFI

#define _JBTYPE long
#define _JBLEN  32
typedef _JBTYPE jmp_buf[_JBLEN];

#else


typedef struct JmpBuf_{
  unsigned long r4;
  unsigned long ebx;
  unsigned long ecx;
  unsigned long edx;
  unsigned long esi;
  unsigned long edi;
  unsigned long ebp;
  unsigned long esp;
  unsigned long eip;
  unsigned long lr;
} JmpBuf;

typedef JmpBuf jmp_buf[1];
#endif

#ifdef __cplusplus
extern "C" {
#endif
int my_setjmp(jmp_buf);
void my_longjmp(jmp_buf, int);

#ifdef __cplusplus
}
#endif


#endif
