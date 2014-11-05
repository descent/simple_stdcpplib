#include "cstring.h"

#include <cstring>

using namespace DS;

bool CString::init(const char *str)
{
  int len = strlen(str);

  if (len >= STRING_LEN)
  {
    strcpy(str_, "?????");
    return false;
  }
  else
  {
    strcpy(str_, str);
    return true;
  }
}

CString& CString::operator= ( const CString& other )
{
  init(other.c_str() );
  return *this;
}
