#ifndef MYIOSTREAM_H
#define MYIOSTREAM_H

#include "type.h"

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
      ofstream():basefield_(DEC)
      {
      }
      ofstream& operator<<(char c);
      ofstream& operator<<(const char *str);
      ofstream& operator<<(int num);
      ofstream& operator<<(double num);
      ofstream& operator<<(const DS::string &str);
      ofstream& operator<<(unsigned int num);
      ofstream& operator<<(ofstream& (*op)(ofstream &)) { return (*op)(*this); }
      void set_basefield(u8 basefield){basefield_ = basefield;}
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


