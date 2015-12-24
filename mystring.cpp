#include "mystring.h"
#include "myiostream.h"
#include "mem.h"

DS::string::string():len_(0), str_(0)
{
}

DS::string::string(const char *str)
{
  len_ = s_strlen(str);
  // str_ = (char *)mymalloc(len_);
  str_ = new char[len_];
  s_strcpy(str_, str);

  cout << "string ctor" << endl;
}

DS::string::~string()
{
  delete [] str_;
  cout << "string ~ctor" << endl;
}

DS::string& DS::string::operator=(const DS::string& s)
{
  //cout << "xxx" << endl;
  delete [] str_;
  len_ = s_strlen(s.c_str());
  str_ = new char[len_];
  s_strcpy(str_, s.c_str());
  return *this;
}

DS::string& DS::string::operator=(const char *str)
{
  delete [] str_;

  len_ = s_strlen(str);
  str_ = new char[len_];
  s_strcpy(str_, str);

  return *this;
}

char& DS::string::operator[](unsigned int idx)
{
}

