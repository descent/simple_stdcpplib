#include "myiostream.h"
#include "myvec.h"
#include "mymap.h"
//#include "mystring.h"
#include "mylist.h"

// #define TEST_BASIC
//#define TEST_MEM_PAGE_LIMIT
//#define TEST_STATIC_OBJ
#define TEST_VIRTUAL_FUNC
//#define TEST_VECTOR
//#define TEST_MAP
//#define TEST_LIST
//#define TEST_MEM_ALLOC_FAIL
//#define SET_SETJMP
//#define TEST_BSS

const int INDEX_MAX = PAGE_SIZE;
const int WHICH_PAGE = PAGE-1;

using namespace DS;

int arr[1024];

class BaseClass
{
  public:
    BaseClass(int base=5): base_(base)
    {
      //cout << "BaseClass: " << base_ << endl;
      printf("BaseClass: %d\n", base_);
    }
    ~BaseClass()
    {
      //cout << "dtor BaseClass: " << endl;
      printf("dtor BaseClass\n");
    }
    virtual void vfunc()
    {
      cout << "Base vfunc: " << base_ << endl;
      //printf("Base vfunc: %d\n", base_);
    }

#ifdef SUPPORT_PURE_VIRTUAL_FUNCTION
    virtual void pf()=0;
#endif
  private:
    int base_;
};

class DeriveClass : public BaseClass
{
  public:
    DeriveClass(int d=10): BaseClass(99), d_(d)
    {
      cout << "DeriveClass: " << d_ << endl;
    }
    virtual void vfunc()
    {
      cout << "derive vfunc: " << d_ << endl;
    }
#ifdef SUPPORT_PURE_VIRTUAL_FUNCTION
    virtual void pf()
    {
      //cout << "pure virtual: " << endl;
      printf("pure virtual:\n");
    }
#endif
  private:
    int d_;
};

#ifdef TEST_STATIC_OBJ
void f1()
{
  static BaseClass obj;
}
#endif


namespace
{
  //char heap[64*10];
}

//#include "bios_call.h"

jmp_buf jbuf;

void test_bss(int *i)
{
  cout << "bss: " << *i << endl; 
}


int mymain()
{
#if 0
#ifdef TEST_BSS
  for (int i=0 ; i < 1024 ; ++i)
  {
    cout << i << ": " << arr[i] << endl;
    test_bss(&arr[i]);
  }
  while(1);
#endif

#ifdef SET_SETJMP
  int jnum = my_setjmp(jbuf);
  if (jnum == 0)
  {
  }
  else
  {
    cout << "longjmp: " << jnum << endl;
    while(1);
  }

  cout << "sizeof(int): " << sizeof(int) << endl;
  my_longjmp(jbuf, 5);
#endif

#if 1
  //bios_read_char();

#ifdef TEST_BASIC
  string s{"1bcd1234"};
  cout << s << " ok" << endl;
  //print_memarea();
  while(1);
#endif

#if 0
  heap[63*1024+1] = 'B'+1;
  char ch = heap[63*1024+1];
  cout << ch << " ok" << endl;
  heap[63*1024+2] = 'B'+2;
  ch = heap[63*1024+2];
  cout << ch << " xx" << endl;
#endif


#ifdef TEST_MEM_PAGE_LIMIT
  extern char heap[];
  int j=0;
  for (int i=0 ; i < INDEX_MAX ; ++i, ++j)
  {
    if (j%26 == 0)
      j=0;
    heap[WHICH_PAGE* PAGE_SIZE +i] = 'A'+ j;
  }

  for (int i=0 ; i < INDEX_MAX ; ++i)
  {
    char cc = heap[WHICH_PAGE* PAGE_SIZE +i];
    //cout << i << ": ";
    //cout << cc << endl;
    //cout << i << ": " << cc << endl;
    cout << i << ": " << cc << endl;
  }
#endif



#ifdef TEST_STATIC_OBJ
  cout << "test static obj" << endl;
  f1();
  cout << "test static obj again" << endl;
  f1();
#endif

#ifdef TEST_VIRTUAL_FUNC

#ifdef SUPPORT_PURE_VIRTUAL_FUNCTION
  BaseClass *bc = 0;
#else
  BaseClass *bc = new BaseClass(1);
#endif
  DeriveClass *dv = new DeriveClass(2);



#ifndef SUPPORT_PURE_VIRTUAL_FUNCTION
  cout << "call bc->vfunc();" << endl;
  bc->vfunc();
#endif


  bc = dv;
  cout << "call dv->vfunc();" << endl;
  bc->vfunc();
#endif

  int i=0;

#ifdef TEST_VECTOR
{
  vector<string> vec;

  vec.push_back("abc");
  vec.push_back("xyz");
  vec.push_back("123");
  vec.push_back("abcdefghijk!@#$%^&*()");

  for (i=0 ; i < vec.size() ; ++i)
    cout << vec[i] << endl;


  cout << "test vec iterator" << endl;
  for (auto it=vec.begin() ; it!=vec.end() ; ++it)
    cout << *it << endl;

}
#endif

#ifdef TEST_MAP
{
  map<string, int> str_map;

  str_map.insert({"zxcv", 5});
  str_map.insert({"abc", 51});
  str_map.insert({"abcdefghqq", 151});
  str_map.insert({"111", 99});

  for (auto it=str_map.begin() ; it!=str_map.end() ; ++it)
    cout << "(" << it->k_ << "," << it->v_ << ")" << endl;

}
#endif


#ifdef TEST_LIST
{
  list<string> list;

  list.push_back("xyz");
  list.push_back("123");
  list.push_back("qwerty");
  cout << "test list" << endl;
  for (auto it=list.begin() ; it!=list.end() ; ++it)
    cout << *it << endl;
}
#endif


#ifdef TEST_MEM_ALLOC_FAIL
  for (i=0 ; i < 100 ; ++i)
  {
    char *c = new char;
    cout << "i: " << i << endl;
  }
  cout << "alloc all memory ok" << endl;
#endif
#endif
#endif
  return 1;
} // end int mymain()
