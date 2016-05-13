#ifndef TYPE_H
#define TYPE_H

#ifdef X86_16
  __asm__(".code16gcc\n");
#endif
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef unsigned long long u64;

#ifdef UEFI
typedef unsigned long size_t;
#else
typedef unsigned int size_t;
#endif

#endif

