#include "mem.h"

#include <stdio.h>

const int PAGE_SIZE = 1024;
const int PAGE = 64;
const int HEAP_SIZE = PAGE * PAGE_SIZE;
char heap[HEAP_SIZE];
unsigned char mem_area[PAGE];
int free_index = 0;

void print_memarea()
{
  printf("free_index: %d\n", free_index);
  for (int i = 0 ; i < PAGE ; ++i)
  {
    if (i % 8 == 0)
      printf("\n");
    printf("%02d ", mem_area[i]);
  }
  printf("\n");
}


namespace
{

// size: 1 means 1K, size max is 64
void *mymalloc_internal(unsigned char size)
{
  if (free_index + size > PAGE)
  {
    return 0;
  }
  char * ptr = heap + free_index * PAGE_SIZE;
  #if 1
  printf("xx free_index: %d\n", free_index);
  printf("xx heap: %p\n", heap);
  printf("xx ptr: %p\n", ptr);
  #endif
  *(mem_area + free_index) = size;

  for (int i = 1 ; i < size ; ++i)
    *(mem_area + free_index + i) = 1;

  free_index += size;
  return (void*)ptr;
}

} // end anonymous namespace

void *mymalloc(u32 size)
{
  u32 page = size / PAGE_SIZE;
  u32 remain = size % PAGE_SIZE;
  if (remain != 0)
    ++page;
  printf("alloc size: %d\n", size);
  printf("alloc page: %d\n", page);
  return mymalloc_internal(page);
}

void myfree(void *ptr)
{
  int index = ((char *)ptr - heap) / PAGE_SIZE;
  unsigned char size = *mem_area;
  for (int i=0 ; i < size ; ++i)
    *(mem_area + i) = 0;
}

#ifdef TEST
int main(int argc, char *argv[])
{
  printf("heap: %p\n", heap);

  #if 0
  char *p1 = (char *)mymalloc(64);
  if (p1 == 0)
    printf("p1 is 0\n");
  else
    printf("p1: %p\n", p1);
  print_memarea(); 
  #else

  print_memarea(); 
  char *p1 = (char *)mymalloc(6*PAGE_SIZE);
  print_memarea(); 

  myfree(p1);
  print_memarea(); 


#if 0
  char *p2 = (char *)mymalloc(3);
  print_memarea(); 
  char *p3 = (char *)mymalloc(2);
  print_memarea(); 
  printf("p1: %p\n", p1);
  printf("p2: %p\n", p2);
  printf("p3: %p\n", p3);

  char *p5 = (char *)mymalloc(54);
  if (p5 == 0)
    printf("p5 is 0\n");
  else
    printf("p5: %p\n", p1);
#endif
  #endif

  return 0;
}
#endif
