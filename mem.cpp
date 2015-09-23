#include "mem.h"


#ifdef STM32

#include "k_stdio.h"
using namespace DS;
#define NL "\r\n"

#else
#include <stdio.h>
#include <unistd.h> // sbrk

#define NL "\n"

#endif


// #define DEBUG_MSG
#ifdef DEBUG_MSG
  #define PF printf
#else
  #define PF(...) 
#endif

#define EXCEED_MEMAREA -1
#define NO_FREE_MEMAREA -2
#define GET_FREE_MEMAREA 0


const int PAGE_SIZE = 1024;
const int PAGE = 64; // how many pages
const int HEAP_SIZE = PAGE * PAGE_SIZE;
char heap[HEAP_SIZE];
// unsigned char mem_area[PAGE];
unsigned short mem_area[HEAP_SIZE/PAGE_SIZE];
unsigned int free_index = 0;

#define PRINT_PTR(p) \
  if (p == 0) \
    printf("p: 0\n"); \
  else \
    printf("p: %p\n", p);

void print_memarea()
{
  printf("----------------");
  printf(NL);
  printf("free_index: %d", free_index);
  printf(NL);
  for (int i = 0 ; i < PAGE ; ++i)
  {
    if (i % 8 == 0)
      printf(NL);
    #ifdef STM32
    printf("%d ", mem_area[i]);
    #else
    printf("%04d ", mem_area[i]);
    #endif
  }
  printf(NL);
  printf("================");
  printf(NL);
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
  PF("old free_index: %d\n", free_index);
  PF("xx heap: %p\n", heap);
  PF("xx ptr: %p\n", ptr);
  *(mem_area + free_index) = size;

  for (int i = 1 ; i < size ; ++i)
    *(mem_area + free_index + i) = 1;

  free_index += size;
  PF("new free_index: %d\n", free_index);
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

  PF("alloc size: %d\n", size);
  PF("alloc page: %d\n", page);
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
  if ((index + size) == free_index)
  {
    PF("\told free_index: %d, index: %d, size: %d\n", free_index, index, size);
    free_index -= size;
    PF("\tmerge free_index: %d\n", free_index);
  }
#endif
}

namespace 
{
  LIST::Header base;
  LIST::Header *freep = 0;
  char *brk_addr;
}

#ifndef STM32
namespace LIST
{
  const int NALLOC = 1024; // minimum units to request

  void print_header(const Header *h, const char *prompt=0)
  {
    if (prompt != 0)
      printf("%s\n", prompt);
    if (h==0)
      printf("self: 0\n");
    else
      printf("self: %p\n", h);
    if (h->s.ptr==0)
      printf("s.ptr: 0\n");
    else
      printf("s.ptr: %p\n", h->s.ptr);
    printf("s.size: %d\n", h->s.size);
  }



  void print_free_list()
  {
    if (freep == 0)
    {
      printf("free list is empty\n");
      return;
    }
    Header *p;

    for (p = freep ; ; p=p->s.ptr)
    {
      if (p == (Header *)brk_addr)
        printf("p: %p (brk addr)\n", p);
      else
        printf("p: %p%s", p, p == &base ? " (base)\n" : "\n");
      if (p->s.ptr == freep)
        break;
    }
  }

  void free(void *ap)
  {
    Header *bp, *p;

    bp = (Header *)ap -1;

    int c=0;
    int i=0;
    for (p=freep ; !(bp > p && bp < p->s.ptr) ; p = p->s.ptr)
    {
      ++c;
      if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      {
	++i;
        break;
      }
    }
    printf("in %s() ## c: %d, i: %d\n", __FUNCTION__, c, i);

    if (bp + bp->s.size == p->s.ptr) // join to upper nbr
    {
      printf("upper nbr\n");
      bp->s.size += p->s.ptr->s.size;
      bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
      bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp) // join to lower nbr
    {
      printf("join lower nbr\n");
      p->s.size += bp->s.size;
      p->s.ptr = bp->s.ptr;
    }
    else
      p->s.ptr = bp;

    freep = p;
  }

  Header *morecore(u32 nu)
  {
    char *cp;
    Header *up;

    if (nu < NALLOC)
      nu = NALLOC;
    cp = (char *)sbrk(nu*sizeof(Header));
    if (cp == (char *)(-1))
      return 0;
    printf("cp (by sbrk): %p\n", cp);
    brk_addr = cp;
    up = (Header*)cp;
    up->s.size = nu;
    free((void*)(up+1));
    return freep;
  }

  void *malloc(u32 nbytes)
  {
    Header *p, *prevp;
    Header *morecore(u32);
    u32 nunits;
    nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1; // avoid use % and /
    print_header(&base);
    if (freep)
    {
      printf("freep: %p\n", freep);
      printf("freep->s.ptr: %p\n", freep->s.ptr);
    }
    else
    {
      printf("freep: 0\n");
      printf("freep->s.ptr: ??\n");
    }

    if ((prevp = freep) == 0) // no free list yet
    {
      base.s.ptr = freep = prevp = &base;
      base.s.size = 0;
    }
    for (p=prevp->s.ptr ; ; prevp = p, p = p->s.ptr)
    {
      if (p->s.size >= nunits)
      {
        if (p->s.size == nunits)
          prevp->s.ptr = p->s.ptr;
        else
        {
          p->s.size -= nunits;
          p += p->s.size;
          p->s.size = nunits;
        }
        freep = prevp;
        return (void *)(p+1);
      }
      if (p == freep)
        if ((p = morecore(nunits)) == 0)
          return 0;
    }

  }

}

#define MALLOC(ptr_var, ptr_name, alloc_byte) \
  printf("-------\n"); \
  char *ptr_var = (char *)LIST::malloc(alloc_byte); \
  printf("\t%s: %p\n", ptr_name, ptr_var); \
  print_header(freep, "freep info:"); \
  printf("=======\n"); 

#include <cstdlib>
using namespace std;
void test_list_malloc()
{
  print_header(&base, "base info:");
  //using namespace LIST;
  LIST::print_free_list();

  char *p1 = (char *)LIST::malloc(2);
  printf("\tp1: %p\n", p1);
  print_header(freep, "freep info:");
  printf("=======\n");


  char *p2 = (char *)LIST::malloc(4);
  printf("\tp2: %p\n", p2);
  print_header(freep, "freep info:");
  printf("=======\n");

  char *p3 = (char *)LIST::malloc(6);
  printf("\tp3: %p\n", p3);
  print_header(freep, "freep info:");
  printf("=======\n");

  LIST::free(p1);
  print_header(freep, "freep info:");
  printf("=======\n");

#if 0
  //MALLOC(p4, "p4", 8)
  char *p4 = (char *)LIST::malloc(8);
  printf("\tp4: %p\n", p4);
  print_header(freep, "freep info:");
  printf("=======\n");
#endif
  LIST::free(p3);
#if 0

#if 1
  printf("-- free p1\n");
  LIST::free(p1);
  #if 0
  printf("-- free p2\n");
  LIST::free(p2);
  #endif
#else
  LIST::free(p2);
#endif
#endif

  LIST::print_free_list();

  //LIST::free(p2);
  #if 0
  char *p3 = (char *)std::malloc(2);
  char *p4 = (char *)std::malloc(4);
  printf("p3: %p\n", p3);
  printf("p4: %p\n", p4);
  #endif
}
#endif // end #ifndef STM32

#ifdef TEST
int main(int argc, char *argv[])
{
  test_list_malloc();
  //printf("heap: %p\n", heap);

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
  PRINT_PTR(p2)
  print_memarea(); 
#endif

// #define TEST_MERGE_FREE_AREA
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
