#ifndef MYIOSTREAM_H
#define MYIOSTREAM_H

#include "type.h"
#include "k_stdio.h"

#define HEX 1
#define DEC 2
#define OCT 3

extern void *__dso_handle;

struct DObjs
{
  void (*dtor_) (void *);
  void *arg_;
  void *dso_handle_;
};

void g_dtor();


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


