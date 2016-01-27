#ifndef MEM_H
#define MEM_H

#include "type.h"

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
