#ifndef CSTRING_H
#define CSTRING_H

#ifdef OS_CPP
  #include <stdio.h>
  #include <cstring>
using namespace std;
#else
  #include "k_string.h"
  #define strlen s_strlen
  #define strcpy s_strcpy
#endif


const int STRING_LEN = 128;

namespace DS
{
  class CString
  {
    public:
      bool init(const char *str);
      bool init(){set_null();}
      CString& operator= ( const CString& other );
      const char *c_str() const
      {
        return str_;
      }
      CString& operator= (const char *s)
      {
        init(s);
        return *this;
      }
      void set_null()
      {
        str_[0] = 0;
      }
      int length() const
      {
        return strlen(str_);
      }
      void print();

    private:
      char str_[STRING_LEN];
  };
}

#endif
