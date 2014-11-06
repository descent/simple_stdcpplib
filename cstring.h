#ifndef CSTRING_H
#define CSTRING_H

#ifdef OS_CPP
#include <stdio.h>
using namespace std;
#else
#include "k_stdio.h"
#define printf myprint
#endif

const int STRING_LEN = 128;

namespace DS
{
  class CString
  {
    public:
      bool init(const char *str);
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
      void print()
      {
        printf(str_);
      }

    private:
      char str_[STRING_LEN];
  };
}

#endif
