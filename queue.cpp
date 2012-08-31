#include "queue.h"

// init: 
// begin_ = end_ = 0;
// q leave one empty space when full
Queue::Queue(int len)
{
  if (len > 1)
  {
    len_ = len;
    q_ = new char[len_];
    begin_ = end_ = 0;
  }
}

bool Queue::push(char ch)
{
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

bool Queue::pop(char &ch)
{
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
