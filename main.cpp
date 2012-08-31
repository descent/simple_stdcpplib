#include "queue.h"
#include <iostream>
#include <cstdlib>

using namespace std;

  Queue q(5);
void push_test(char c)
{
    cout << "  begin: " << q.begin() << endl;
    cout << "  end: " << q.end() << endl;
    if (q.push(c))
      cout << "push: " << c << endl;
    else
      cout << "cannot push: " << c << endl;
    cout << "    begin: " << q.begin() << endl;
    cout << "    end: " << q.end() << endl;
    q.print();
    cout << "==============================" << endl;
}

void pop_test()
{
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
    cout << "==============================" << endl;
}

// how to autotest for class Queue
int main(void)
{
  char test_pattern[]=
  {
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'i',
    'j',
    'k',
    'l',
    'm',
    'n',
    'o',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
  };
  srand(time(NULL));

  int times = 0;
  while(1)
  {
    int num = rand() % (sizeof(test_pattern)/sizeof(char));
    cout << "  num: " << num << endl;

    if (num % 2 == 0)
      push_test(test_pattern[num]);
    else
      pop_test();

    ++times;
    if (times >= 100)
      break;
  }

  return 0;
}
