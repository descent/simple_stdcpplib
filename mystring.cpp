#include "mystring.h"
DS::string::string(const char *str)
{
}

DS::string& DS::string::operator=(const DS::string& s)
{
  return *this;
}

DS::string& DS::string::operator=(const char *s)
{
  return *this;
}

char& DS::string::operator[](unsigned int idx)
{
}
