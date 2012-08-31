#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

using namespace std;

class Queue
{
  public:
    explicit Queue(int len);
    bool push(char ch);
    bool pop(char &ch);
    void print()
    {
      for (int i=0 ; i < len_ ; ++i)
        cout << *(q_ + i) << " ";
      cout << endl;
    }
  private:
    int begin() const {return begin_;}
    int end() const {return end_;}
    bool can_push()
    {
      int next_begin = ((begin() + 1) % len_);
      if (next_begin == end())
        return false;
      else
        return true;
    }
    bool can_pop()
    {
      if (begin() == end())
        return false;
      else
        return true;
    }
    char *q_;
    int len_;
    int begin_, end_;
};

#endif
