#ifndef MYSTRING_H
#define MYSTRING_H

#ifdef X86_16
  __asm__(".code16gcc\n");
#endif

#include "type.h"
#include "k_string.h"

namespace DS
{
  /**
   * \brief like std::string
   */
  class string
  {
    public:
      explicit string();
      string(const char *str);
      string(const string &s);
      string(string &&s);
      ~string();
      string& operator=(const string& s);
      string& operator=(const char *str);
      //bool operator<(const char *s);
      //bool operator>(const char *s);
      char& operator[](unsigned int idx);
      const char* c_str() const{return str_;}
      u32 length() const {return len_;}
      #if 0
      bool operator>(char const * rhs )
      {
      }
      #endif
    private:
      int generate_string(const char *str, int len);
      char *str_;
      u32 len_;
  };

}

#if 1
static inline bool operator>(const DS::string& lhs, const DS::string& rhs)
{
  if (s_strcmp(lhs.c_str(), rhs.c_str()) > 0)
    return true;
  else
    return false;
}
static inline bool operator>(const DS::string& lhs, const char* rhs)
{
  //int ret = s_strcmp(lhs.c_str(), rhs);

  if (s_strcmp(lhs.c_str(), rhs) > 0)
    return true;
  else
    return false;
}

static inline bool operator<(const DS::string& lhs, const char* rhs)
{
  //int ret = s_strcmp(lhs.c_str(), rhs);

  if (s_strcmp(lhs.c_str(), rhs) < 0)
    return true;
  else
    return false;
}

static inline bool operator<(const DS::string& lhs, const DS::string& rhs)
{
  //int ret = s_strcmp(lhs.c_str(), rhs.c_str());

  if (s_strcmp(lhs.c_str(), rhs.c_str()) < 0)
    return true;
  else
    return false;
}

DS::string operator+(const DS::string& lhs, const DS::string& rhs);
#endif

#endif
