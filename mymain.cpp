#define USE_STDPERIPH_DRIVER

#include "stm32f10x.h"
#include "stm32_p103.h"

#include "bst.h"
#include "mem.h"
#include "myiostream.h"
#include "mystring.h"
#include "myvec.h"
#include "mylist.h"
#include "mymap.h"

#if 0
#include "k_stdio.h"
#include "s_eval.h"
#include "gdeque.h"
#include "cstring.h"
#endif

using namespace DS;

uint8_t get_byte()
{
  while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);

  return (USART_ReceiveData(USART2) & 0x7F);
}

#if 0
void myfree(void *ptr)
{
}

void *mymalloc(int size)
{
  static char mem[256];
  return mem;
}
#endif

void *operator new(unsigned int s)
{
  void *ptr = mymalloc(s);

  if (ptr == 0)
    THROW(NOFREE_MEM);

  return ptr;
}

void *operator new[](unsigned int s)
{
  //cout << "s: " << s << endl;
  // printf("s: %d\r\n", s);

  void *ptr = mymalloc(s);

  if (ptr == 0)
    THROW(NOFREE_MEM);

  return ptr;
}

void operator delete(void *p)
{
  myfree(p);
}

void operator delete[](void *p)
{
  myfree(p);
}

void test_bst()
{
  int i=0;

  GNode<int, int> *root = 0;
  for (i=0 ; i < 1000 ; ++i)
  {
    cout << "insert:" << endl;
    root = insert(root, 8, 7);
  }
  //root = insert(root, 4, 7);
  //root = insert(root, 14, 7);
  print_tree(root);
}

void test_vec()
{
  DS::vector<int> vec;

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);
  vec.push_back(6);
  for (int i=0 ; i < vec.length() ; ++i)
  {
    cout << vec[i] << endl;
  }
  cout << vec.max_size() << endl;
}

typedef void (*Fp)();

static int value=6;

extern "C"
{

int main(void)
{
  init_rs232();
  USART_Cmd(USART2, ENABLE);
  {
    cout << "abv" << endl;
  }
  {
    map<int, int> mymap;

    mymap.insert(15, 65);
    mymap.insert(5, 165);
    mymap.insert(25, 365);
    mymap.insert(1, 12);
    mymap.insert(191, 23);

    auto it = mymap.begin();
    for (it ; it != mymap.end() ; ++it)
    {
      //(*it).k_;
      cout << "(*it).k: "<< (*it).k_ << endl;
    }
    while(1);
  }

{
  list<int> list;

  list.push_back(1);
  //print_memarea();
  list.push_back(2);
  //print_memarea();
  list.push_back(3);
  //print_memarea();

  //auto it = list.begin();
  auto it = list.begin();
  //cout << *it << endl;
  for (int e : list)
    cout << e << endl;
#if 0
  for (it ; it != list.end() ; ++it)
    cout << *it << endl;
#endif
}
  print_memarea();
  while(1);

  extern unsigned int __start_global_ctor__;
  extern unsigned int __end_global_ctor__;
  unsigned int *start = &__start_global_ctor__;
  unsigned int *end = &__end_global_ctor__;

{
  int ptr = (int)(&value);

  cout << "ptr: " << hex << ptr << endl;
  while(1);
}
#if 1
  for (unsigned int *i = start; i != end; ++i)
  {
    Fp fp = (Fp)(*i);
    (*fp)();
  }
#endif

  int val=98;
  double d_val=3.56;



  //char *p1 = (char *)mymalloc(4);
#if 0
  char *p1 = new char;
  print_memarea();
  delete p1;
  print_memarea();
#endif

#if 0
  {
    string str("i am mystring");
  }

  printf("test bst: %d, d_val: %f\r\n", val, d_val);

  cout << "test bst: " << val << endl;
#endif
  int i=100;
  print_memarea();
  TRY
  {
    test_vec();
    //test_bst();
  }
  CATCH(NOFREE_MEM)
  {
    cout << "no mem, i: " << i << endl;
  }
  ETRY

  // print_memarea();
  while(1);


  cout << endl;

  {
    GNode<double, int> *root = 0;

    cout << "sizeof(double): " << sizeof(double) << endl;

    root = insert(root, 8.1, 7);
    root = insert(root, 4.2, 7);
    root = insert(root, 14.3, 7);
    print_tree(root);
    print_memarea();
  }

  while(1);

  cout << endl;


  {
    GNode<DS::string, int> *root = 0;
    root = insert(root, "def", 7);
    root = insert(root, "xyz", 5);
    root = insert(root, "abc", 8);
    print_tree(root);
  }

  while(1);

  return 0;

}

}
