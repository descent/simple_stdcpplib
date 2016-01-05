#ifndef MYIOSTREAM_H
#define MYIOSTREAM_H

#include "type.h"

#ifdef TEST

#include <cstdio>
using namespace std;

#else

#include "k_stdio.h"

#include "my_setjmp.h"
#endif



#if 0
#define setjmp my_setjmp
#define longjmp my_longjmp

extern  int ex_code;

#define TRY do { switch((ex_code = setjmp(ex_buf__))) { case 0:
#define CATCH(x) break; case x : 
#define ETRY break; } } while(0);
#define THROW(x) longjmp(ex_buf__, x)

#define NOFREE_MEM 5

jmp_buf ex_buf__;

extern void *__dso_handle;

struct DObjs
{
  void (*dtor_) (void *);
  void *arg_;
  void *dso_handle_;
};

void g_dtor();
#endif

#define HEX 1
#define DEC 2
#define OCT 3

namespace DS
{
  class string;
  //extern const char *endl;


  class ofstream
  {
    public:
      ofstream(int id=0):basefield_(DEC)
      {
        id_ = id;
        printf("i am cout ctor: %d\r\n", id_);
      }
      ~ofstream()
      {
        printf("i am cout dtor: %d\r\n", id_);
      }
      ofstream& operator<<(char c);
      ofstream& operator<<(const char *str);
      ofstream& operator<<(int num);
      ofstream& operator<<(double num);
      ofstream& operator<<(const DS::string &str);
      ofstream& operator<<(unsigned int num);
      ofstream& operator<<(ofstream& (*op)(ofstream &)) { return (*op)(*this); }
      ofstream& operator<<(u32 *ptr);
      ofstream& operator<<(s32 *ptr);
      void set_basefield(u8 basefield){basefield_ = basefield;}
      int id_;
    private:
      u8 basefield_;
  };


  extern ofstream cout;

  // ref: c++ 標準庫 the 2nd p776
  static inline ofstream& endl(ofstream &stream)
  {
    stream << "\r\n";
    return stream;
  }

  static inline ofstream& hex(ofstream &stream)
  {
    stream.set_basefield(HEX);
    return stream;
  }
  static inline ofstream& dec(ofstream &stream)
  {
    stream.set_basefield(DEC);
    return stream;
  }
}


#endif


