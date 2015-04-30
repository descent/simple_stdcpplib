#include "mem.h"

#include <stdio.h>

#define EXCEED_MEMAREA -1
#define NO_FREE_MEMAREA -2
#define GET_FREE_MEMAREA 0

const int PAGE_SIZE = 1024;
const int PAGE = 64;
const int HEAP_SIZE = PAGE * PAGE_SIZE;
char heap[HEAP_SIZE];
unsigned char mem_area[PAGE];
int free_index = 0;

void print_memarea()
{
  printf("================\n");
  printf("free_index: %d\n", free_index);
  for (int i = 0 ; i < PAGE ; ++i)
  {
    if (i % 8 == 0)
      printf("\n");
    printf("%02d ", mem_area[i]);
  }
  printf("\n");
  printf("================\n");
}


namespace
{

int is_enough(int index, u8 size)
{
  if (index + size > PAGE) 
  {
    printf("EXCEED_MEMAREA\n");
    return EXCEED_MEMAREA;
  }
  
  if (*(mem_area + index + size - 1) != 0)
  {
    printf("NO_FREE_MEMAREA\n");
    return NO_FREE_MEMAREA;
  }

  return GET_FREE_MEMAREA;
}

bool find_free_index(int from, int &index)
{
  for (int i = 0 ; i < PAGE-from ; ++i)
  {
    if (*(mem_area + from + i) == 0)
    {
      index = i + from;
      return true;
    }
  }
  return false;
}

bool search_free_area(u8 size)
{
  int status;
  int tmp_index = 0;
  int new_index;
  int ret;

  ret = find_free_index(tmp_index, new_index);
  if (ret == false)
    return false;

  while(1)
  {
    status = is_enough(new_index, size);
    if (status == EXCEED_MEMAREA)
    {
      printf("EXCEED_MEMAREA\n");
      return false;
    }
    if (status == GET_FREE_MEMAREA)
    {
      free_index = new_index;
      printf("new_index: %d\n", new_index);
      return true;
    }

    tmp_index = new_index + size;
    ret = find_free_index(tmp_index, new_index);
    printf("still search tmp_index: %d\n", tmp_index);
    printf("still search new_index: %d\n", new_index);
    if (ret == false)
      return false;
  }
}

// size: 1 means 1K, size max is 64
void *mymalloc_internal(u8 size)
{
  if (is_enough(free_index, size) != GET_FREE_MEMAREA)
  {
    printf("not enough: free_index: %d, size: %d\n", free_index, size);
    if (search_free_area(size) == false)
      return 0;
  }
  char * ptr = heap + free_index * PAGE_SIZE;
  #if 1
  printf("old free_index: %d\n", free_index);
  printf("xx heap: %p\n", heap);
  printf("xx ptr: %p\n", ptr);
  #endif
  *(mem_area + free_index) = size;

  for (int i = 1 ; i < size ; ++i)
    *(mem_area + free_index + i) = 1;

  free_index += size;
  printf("new free_index: %d\n", free_index);
  return (void*)ptr;
}

} // end anonymous namespace

void *mymalloc(u32 size)
{
  printf("mymalloc: %d byte(s)\n", size);

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
  printf("myfree: %p\n", ptr);
  int index = ((char *)ptr - heap) / PAGE_SIZE;
  printf("index: %d\n", index);
  unsigned char size = *(mem_area + index);
  printf("size: %d\n", size);
  for (int i=0 ; i < size ; ++i)
    *(mem_area + index + i) = 0;

#if 1
  // 假如 free 掉的這塊, 可以和 free_index 合併, 就可以移動 free_index
  if ((index + size) == free_index);
  {
    free_index -= size;
  }
#endif
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

#if 0
  print_memarea(); 
  char *p1 = (char *)mymalloc(6*PAGE_SIZE);
  print_memarea(); 

  myfree(p1);
  print_memarea(); 

  char *p2 = (char *)mymalloc(60*PAGE_SIZE);
  if (p2 == 0)
    printf("p2 is 0\n");
  else
    printf("p2: %p\n", p2);
  print_memarea(); 
#endif

#define TEST_MERGE_FREE_AREA
#ifdef TEST_MERGE_FREE_AREA
  char *p1 = (char *)mymalloc(4*PAGE_SIZE);
  char *p2 = (char *)mymalloc(2*PAGE_SIZE);
  print_memarea(); 
  myfree(p2);

  p2 = (char *)mymalloc(60*PAGE_SIZE);
  if (p2 == 0)
    printf("p2: 0\n");
  else
    printf("p2: %p\n", p2);

  print_memarea(); 
#endif

#ifdef TEST_ALLOC_THEN_FREE
  char *p1 = (char *)mymalloc(5*PAGE_SIZE);
  char *p2 = (char *)mymalloc(10*PAGE_SIZE);
  char *p3 = (char *)mymalloc(48*PAGE_SIZE);
  print_memarea(); 

  myfree(p2);
  print_memarea(); 

  char *p4 = (char *)mymalloc(6*PAGE_SIZE);
  if (p4 == 0)
    printf("p4 is 0\n");
  else
    printf("p4: %p\n", p4);

  print_memarea(); 

  char *p5 = (char *)mymalloc(5*PAGE_SIZE);
  if (p5 == 0)
    printf("p5 is 0\n");
  else
    printf("p5: %p\n", p5);
#endif

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
