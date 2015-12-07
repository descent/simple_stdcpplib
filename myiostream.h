#ifndef MYIOSTREAM_H
#define MYIOSTREAM_H

#include "mystring.h"

namespace DS
{
  extern const char *endl;

  class ofstream
  {
    public:
      ofstream& operator<<(char c);
      ofstream& operator<<(const char *str);
      ofstream& operator<<(int num);
      ofstream& operator<<(double num);
      ofstream& operator<<(const DS::string &str);
      ofstream& operator<<(unsigned int num);
    private:
  };


  extern ofstream cout;
}


#endif


