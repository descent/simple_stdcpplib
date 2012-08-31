#include "queue.h"

// how to autotest for class Queue
int main(void)
{
  Queue q(5);
  q.push('a');
  q.push('b');
  q.push('c');
  q.push('d');
  q.push('e');
  q.push('f');
  q.push('g');
  q.print();
  return 0;
}
