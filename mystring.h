#ifndef MYSTRING_H
#define MYSTRING_H

namespace DS
{
  class string
  {
    public:
      explicit string(const char *str);
    private:
      string& operator=(const string& s);
      string& operator=(const char *s);
      char& operator[](unsigned int idx);


  };
}

#endif
