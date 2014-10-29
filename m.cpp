#include "mydeque.h"
#include <iostream>
#include <cstdlib>

using namespace std;

#if 0
void push_test(Queue &q, char c)
{
    cout << "--------- push ---------------------" << endl;
    cout << "  begin: " << q.begin() << endl;
    cout << "  end: " << q.end() << endl;
    if (q.push(c))
      cout << "push: " << c << endl;
    else
      cout << "cannot push: " << c << endl;
    cout << "    begin: " << q.begin() << endl;
    cout << "    end: " << q.end() << endl;
    if (!q.print())
      cout << "  q.print fail" << endl;
}

void pop_test(Queue &q)
{
    cout << "======== pop ======================" << endl;
    char c;
    cout << "  begin: " << q.begin() << endl;
    cout << "  end: " << q.end() << endl;

    if (q.pop(c))
      cout << "pop: " << c << endl;
    else
      cout << "pop fail" << endl;

    cout << "    begin: " << q.begin() << endl;
    cout << "    end: " << q.end() << endl;
    q.print();
}

#endif

#define POP_FRONT_TEST \
  if (mydeque.pop_front(ch) == true) \
    cout << "pop front ch: " << ch << endl; \
  else \
    cout << "pop front fail\n"; 

#define POP_BACK_TEST \
  if (mydeque.pop_back(ch) == true) \
    cout << "pop back ch: " << ch << endl; \
  else \
    cout << "pop back fail\n"; 

#define PUSH_BACK_TEST(ch) \
  if (mydeque.push_back(ch) == false) \
    cout << "push back fail\n";

#define PUSH_FRONT_TEST(ch) \
  if (mydeque.push_front(ch) == false) \
    cout << "push front fail\n";
// how to autotest for class Queue
int main(void)
{
  MyDeque mydeque(4);

  PUSH_BACK_TEST('a')
  PUSH_BACK_TEST('b')
  //PUSH_BACK_TEST('c')
  //PUSH_BACK_TEST('d')
  PUSH_FRONT_TEST('1');
  PUSH_FRONT_TEST('2');

  mydeque.print();
  char ch;

  POP_FRONT_TEST
  POP_FRONT_TEST
  POP_FRONT_TEST
  POP_FRONT_TEST
  POP_FRONT_TEST

  POP_BACK_TEST

  mydeque.print();

  return 0;
}
