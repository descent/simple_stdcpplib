#include "gdeque.h"

#include <string>

using namespace std;

export template <typename ElmType> class Deque;

template <typename ElmType>
bool Deque<ElmType>::init()
{
  len_ = DEQUE_LEN;
  begin_ = end_ = 0;
}

template <typename ElmType>
bool Deque<ElmType>::push_back(ElmType &ch)
{
  if (ready() == false) 
    return false;
// copy ch to begin point
// ++begin

  bool ret = true;
  if (can_push())
  {
    *(q_ + begin_) = ch;
    begin_ = ((begin_ + 1) % len_);
  }
  else
    ret = false;
  return ret;
}

template <typename ElmType>
bool Deque<ElmType>::push_front(int ch)
{
  if (ready() == false) 
    return false;
  bool ret = true;

  // has space to push
  if (can_push())
  {
    end_ = ((end_ + len_ - 1) % len_);
    *(q_ + end_) = ch;
  }
  else
    ret = false;
  return ret;
}


template <typename ElmType>
bool Deque<ElmType>::pop_front(ElmType &ch)
{
  if (ready() == false) 
    return false;
// return end point value, ++end
  bool ret = true;
  if (can_pop())
  {
    ch = *(q_ + end_);
    end_ = ((end_ + 1) % len_);
  }
  else
  {
    ret = false;
  }
  return ret;
}

template <typename ElmType>
bool Deque<ElmType>::pop_front()
{
  ElmType ch;
  return pop_front(ch);
}

template <typename ElmType>
bool Deque<ElmType>::pop_back(int &ch)
{
  if (ready() == false) 
    return false;

  bool ret = true;
  if (can_pop())
  {
    begin_ = ((begin_ - 1) % len_);
    ch = *(q_ + begin_);
  }
  else
  {
    ret = false;
  }
  return ret;
}

template <typename ElmType>
bool Deque<ElmType>::back(int i, ElmType &elm)
{
  if (ready() == false) 
    return false;

  bool ret = true;

  int b = ((begin_ - i + len_) % len_);

  if (b == end())
  {
    ret = false;
  }
  else
  {
    elm = *(q_ + b - 1);
  }
  return ret;
}

#define TEST_PUSH_BACK(type, val) \
{ \
  type elm(val); \
  if (deque.push_back(elm) == false) \
  { \
    cout << "push '" << elm << "' fail" << endl; \
    deque.pop_front(); \
    deque.push_back(elm); \
  } \
}

#define TEST_BACK(index, type) \
{ \
  type elm; \
  if (deque.back(index, elm)) \
    cout << elm << endl; \
  else \
    cout << index << ": fail" << endl; \
}

#if 0
int main(int argc, char *argv[])
{
  Deque<string> deque;

  deque.init();

  string a("abc");
  deque.push_back(a);
  a="def";
  deque.push_back(a);
  deque.print();
  TEST_BACK(0, string)
  TEST_BACK(1, string)
  TEST_BACK(2, string)
  TEST_BACK(3, string)
  TEST_PUSH_BACK(string, "123")
  deque.print();
  return 0;
}
#endif
