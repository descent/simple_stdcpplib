#ifndef MEM_H
#define MEM_H

#include "x86_16.h"
#include "type.h"

#ifdef X86_16
const int PAGE_SIZE = 128;
const int PAGE = 80; // how many pages
#else
const int PAGE_SIZE = 1024;
const int PAGE = 64; // how many pages
#endif
const int HEAP_SIZE = PAGE * PAGE_SIZE;

void *mymalloc(u32 size);
void myfree(void *ptr);
void print_memarea();

namespace LIST
{
  typedef long Align;
  union Header
  {
    struct
    {
      union Header *ptr;
      u32 size;
    }s;
    Align x;
  };

}

#endif
