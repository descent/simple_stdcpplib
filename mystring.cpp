#include "mystring.h"
#include "myiostream.h"
#include "mem.h"

#ifdef TEST
#include <cstdio>
using namespace std;
#endif

DS::string::string():len_(0), str_(0)
{
  std::printf("1 ctor\n");
}

DS::string::string(const char *str)
{
  generate_string(str, s_strlen(str));

  std::printf("2 ctor\n");
  //cout << "string ctor" << endl;
}

DS::string::string(const string &s)
{
  generate_string(s.c_str(), s.length());
  std::printf("3 ctor\n");
}

DS::string::~string()
{
  std::printf("11 dtor:%s\n", str_);
  delete [] str_;
  //cout << "string ~ctor" << endl;
}

DS::string& DS::string::operator=(const DS::string& s)
{
  std::printf("1 op=\n");
  delete [] str_;

  generate_string(s.c_str(), s.length());
  return *this;
}

DS::string& DS::string::operator=(const char *str)
{
  std::printf("2 op=\n");
  delete [] str_;

  generate_string(str, s_strlen(str));
  return *this;
}

int DS::string::generate_string(const char *str, int len)
{
  len_ = len;
  str_ = new char[len_];
  s_strcpy(str_, str);
  return 0;
}

char& DS::string::operator[](unsigned int idx)
{
  // don't check idx range
  return str_[idx];
}

#ifdef TEST

DS::string f1()
{
  std::printf("bb\n");
  DS::string s1{"return str"};
  std::printf("ee\n");
  return s1; 
}

int main(int argc, char *argv[])
{
  DS::string s1{"123"};
  DS::string s2{"456"};

  char ch = s1[2];
  printf("ch: %c\n", ch);

  if (s1 < s2)
  {
    printf("s1 < s1\n");
  }
  else
  {
    printf("s1 >= s1\n");
  }

  DS::string s3{s1};
  s2=s1;
  printf("s1: %s\n", s1.c_str());
  printf("s2: %s\n", s2.c_str());
  printf("s3: %s\n", s3.c_str());
  s1="555";
  printf("s1: %s\n", s1.c_str());
  printf("s3: %s\n", s3.c_str());
  DS::string f1_str{"xxx"};
  f1_str = f1();
  printf("f1_str: %s\n", f1_str.c_str());
  DS::string s5;

  //s5=DS::string("666");
  s5="666";

  //std::cout << s1.c_str() << std::endl;

  return 0;
}
#endif
