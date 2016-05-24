#include "mystring.h"
#include "myiostream.h"
#include "mem.h"

#ifdef TEST
#include <cstdio>
using namespace std;
#else
// #define std DS
#endif

DS::string::string():len_(0), str_(0)
{
#ifdef TEST
  std::printf("1 ctor\n");
#endif
}

DS::string::string(const char *str)
{
  generate_string(str, s_strlen(str));

#ifdef TEST
  std::printf("const char *str ctor\n");
#endif
}

DS::string::string(string &&s)
{
  str_ = s.str_;
  len_ = s.len_;
  s.str_ = 0;
  s.len_ = 0;
#ifdef TEST
  std::printf("move ctor\n");
#endif
}

DS::string::string(const string &s)
{
  generate_string(s.c_str(), s.length());

#ifdef TEST
  std::printf("copy ctor\n");
#endif
}

DS::string::~string()
{
#ifdef TEST
  std::printf("11 dtor:%s\n", str_);
#endif
  delete [] str_;
  //cout << "string ~ctor" << endl;
}

DS::string& DS::string::operator=(const DS::string& s)
{
#ifdef TEST
  std::printf("1 op=\n");
#endif
  delete [] str_;

  generate_string(s.c_str(), s.length());
  return *this;
}

DS::string& DS::string::operator=(const char *str)
{
#ifdef TEST
  std::printf("2 op=\n");
#endif
  delete [] str_;

  generate_string(str, s_strlen(str));
  return *this;
}


int DS::string::generate_string(const char *str, int len)
{
  len_ = len;
  str_ = new char[len_+1];
  stringncopy(str_, str, len);
  str_[len_] = '\0';
  return 0;
}

char& DS::string::operator[](unsigned int idx)
{
  // don't check idx range
  return str_[idx];
}

DS::string operator+(const DS::string& lhs, const DS::string& rhs)
{
#ifdef TEST
  printf("operator+\n");
#endif

  u32 lhs_len = lhs.length();
  u32 rhs_len = rhs.length();
  char *s = new char[lhs_len + rhs_len + 1];

  stringncopy(s, lhs.c_str(), lhs_len);
  stringncopy(s + lhs_len, rhs.c_str(), rhs_len);
  s[lhs_len + rhs_len] = '\0';
  
  DS::string ns{s};
  delete s;
  return ns;
}

#ifdef TEST
#include <stdio.h>
#include <utility>

void f3(DS::string s)
{
  printf("f3 s: %s\n", s.c_str());
}

DS::string f2()
{
  DS::string s1{"f2"};
  return s1;
}

DS::string f1()
{
  std::printf("bb\n");
  DS::string s1{"return str"};
  std::printf("ee\n");
  return s1; 
}

int main(int argc, char *argv[])
{
  DS::string s1=f2();
  printf("s1: %s\n", s1.c_str());
  f3(std::move(s1));
  printf("s1: %s\n", s1.c_str());
  printf("s1.length(): %d\n", s1.length());

#if 0
  DS::string s1{"123"};
  DS::string s2{"456"};
  printf("s1: %s\n", s1.c_str());

  DS::string s3{s1 + s2};
  printf("s3: %s\n", s3.c_str());

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
#endif
  return 0;
}
#endif
