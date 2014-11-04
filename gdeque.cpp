#include "gdeque.h"

#include <string>

using namespace std;

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
