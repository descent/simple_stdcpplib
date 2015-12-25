#include "queue.h"
#include <iostream>
#include <cstdlib>

using namespace std;

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

// how to autotest for class Queue
int main(void)
{
  for (int i= -100; i < 100 ; ++i)
  {

    Queue q(i);
    cout << "q.len(): " << q.len() << endl;
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
    cout << "times:" << times << "  num: " << num << endl;

    if (num % 2 == 0)
      push_test(q, test_pattern[num]);
    else
      pop_test(q);

    ++times;
    if (times >= 100)
      break;
  }

  }
  return 0;
}
