#ifndef MYDEQUE_H
#define MYDEQUE_H

#ifdef X86_16
  __asm__(".code16gcc\n");
#endif

#include <iostream>

using namespace std;

class MyDeque
{
  public:
    explicit MyDeque(int len);
    bool push_back(char ch);
    bool pop_front(char &ch);
    bool push_front(char ch);
    bool pop_back(char &ch);

    int len() const {return len_;}
    int begin() const {return begin_;}
    int end() const {return end_;}
    bool print()
    {
      cout << "begin: " << begin_ << endl;
      cout << "end: " << end_ << endl;
      if (ready() == false) return false;
      cout << "-- ";
      int e = end();
      for (int i=e ; i != begin() ; )
      {
        cout << *(q_ + i) << " ";
        i = (i + 1) % len_;
      }
      cout << " --" << endl;
      return true;
    }
    bool ready() const
    {
      //cout << "len_:" << len_ << endl;
      if (len_ > 1)
        return true;
      else
        return false;
    }
  private:
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
    int begin_front_, end_front_;
};

#endif
