#include "cstring.h"

#ifdef OS_CPP
#else
  #include "k_stdio.h"
#endif

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

void CString::print()
{
}
