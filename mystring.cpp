#include "mystring.h"

#ifndef TEST_MYSTRING
#include "myiostream.h"
#include "mem.h"
#endif

#if 0
DS::ofstream& DS::operator<<(DS::ofstream& ofs, const DS::string &str)
{
  return ofs << str.c_str();
}
#endif

#ifdef TEST_MYSTRING
#include <cstdio>

#define TEST_MACRO(assign, count, ...) \
{ \
  std::printf(__VA_ARGS__); \
  if (assign) \
    id_ = count; \
  std::printf("\tid_: %d\n", id_); \
  ++count; \
}

using namespace std;
#else
// #define std DS
#endif

#ifdef TEST_MYSTRING
u32 DS::string::ctor_time_ = 0;
u32 DS::string::dtor_time_ = 0;
#endif

DS::string::string():len_(0), str_(0)
{
#ifdef TEST_MYSTRING
  TEST_MACRO(1, ctor_time_, "def ctor, count: %d\n", ctor_time_)
#endif
}

#if 1
DS::string::string(const char *str)
{
  generate_string(str, s_strlen(str));

#ifdef TEST_MYSTRING
  TEST_MACRO(1, ctor_time_, "ctor: const char *str, %s, count: %d\n", str, ctor_time_)
#endif
}
#endif

#ifdef MOVE_SEMANTIC
#if __cplusplus >= 201103L
DS::string::string(string &&s)
{
#ifdef TEST_MYSTRING
  TEST_MACRO(1, ctor_time_, "move ctor: string &&s, %s, count: %d\n", s.c_str(), ctor_time_)
#endif
  str_ = s.str_;
  len_ = s.len_;
  s.str_ = 0;
  s.len_ = 0;
}
#endif
#endif

DS::string::string(const string &s)
{
  generate_string(s.c_str(), s.length());

#ifdef TEST_MYSTRING
  TEST_MACRO(1, ctor_time_, "copy ctor: string &s, %s, count: %d\n", s.c_str(), ctor_time_)
#endif
}

DS::string::~string()
{
#ifdef TEST_MYSTRING
  TEST_MACRO(0, dtor_time_, "dtor: str_: %s, count: %d\n", str_, dtor_time_)
#endif
  delete [] str_;
  //cout << "string ~ctor" << endl;
}

void DS::string::swap(string &s1, string &s2)
{
  char *tmp_str;
  u32 tmp_len;

  tmp_str = s1.str_;
  tmp_len = s1.len_;

  s1.str_ = s2.str_;
  s1.len_ = s2.len_;

  s2.str_ = tmp_str;
  s2.len_ = tmp_len;
  
}

DS::string& DS::string::operator=(const DS::string& s)
{
//ref: http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
#ifdef TEST_MYSTRING
  std::printf("1 op=\n");
#endif
  string tmp{s};

  swap(*this, tmp);

  //delete [] str_;
  //generate_string(s.c_str(), s.length());
  return *this;
}

#ifdef MOVE_SEMANTIC
#if __cplusplus >= 201103L
DS::string& DS::string::operator=(DS::string&& s)
{
#ifdef TEST_MYSTRING
  std::printf("move op=\n");
#endif

  str_ = s.str_;
  len_ = s.len_;
  s.str_ = 0;
  s.len_ = 0;
  return *this;
}
#endif
#endif

DS::string& DS::string::operator=(const char *str)
{
#ifdef TEST_MYSTRING
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
#ifdef TEST_MYSTRING
  printf("operator+, %s, %s\n", lhs.c_str(), rhs.c_str());
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

#ifdef TEST_MYSTRING
#include <utility>
#include <memory>
#include <vector>

#include <stdio.h>
#include <time.h>

#define TEST_MOVE_SEMANTIC
//#define TEST_ADD_STRING
//#define TEST_OP_ASSIGN

#if 1
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
#endif

int main(int argc, char *argv[])
{
#ifdef TEST_UNIQUE_PTR
  std::unique_ptr<DS::string> ptr{new DS::string{"123"}};
  std::unique_ptr<DS::string> ptr2;

  printf("ptr1: %s\n", ptr->c_str());
  ptr2 = std::move(ptr);
  printf("ptr2: %s\n", ptr2->c_str());
  printf("ptr1: %s\n", ptr->c_str());
#endif

#ifdef TEST_MOVE_SEMANTIC

#if 0
  std::vector<DS::string> v;
  
  v.push_back(DS::string{"456"});
  v.push_back(DS::string{"abc"});
  v.push_back(DS::string{"xyz"});

  for (auto &i: v)
    printf("%s\n", i.c_str());
#endif

#if 1

  DS::string s1;
  s1 = f2();
  #if 1
  printf("s1: %s\n", s1.c_str());
  //f3(std::move(s1));
  f3((DS::string &&)(s1));
  //f3((s1));
  printf("s1: %s\n", s1.c_str());
  printf("s1.length(): %d\n", s1.length());
  #endif

#endif
#endif

#ifdef TEST_ADD_STRING
  DS::string str1;
  DS::string str2{"12"};
  DS::string str3{"34"};
  #if 0
  printf("expr: \"ab\" + str2 + \"Hello\" + str3\n");
  struct timespec time1;
  struct timespec time2;
  clock_gettime(CLOCK_REALTIME, &time1);
  str1 = "ab" + str2 + "Hello" + str3;
  clock_gettime(CLOCK_REALTIME, &time2);

  printf("time diff: %ld\n", time2.tv_nsec - time1.tv_nsec);
  #endif
#endif

#ifdef TEST_OP_ASSIGN
  DS::string str1{"ABC"};
  DS::string str2;

  str2 = str1;
  printf("str1: %s\n", str1.c_str());
  printf("str2: %s\n", str2.c_str());
#endif

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
#endif // #ifdef TEST_MYSTRING
