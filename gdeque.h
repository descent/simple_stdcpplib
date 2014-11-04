/*
 * g: generic
 * gdeque: generic deque
 */

#ifndef GDEQUE_H
#define GDEQUE_H

#include <iostream>
using namespace std;
//namespace DS
//{

const int DEQUE_LEN = 3;

template <typename ElmType>
class Deque
{
  public:
    //explicit MyDeque();
    bool init();


    bool push_back(ElmType &ch);
    bool back(int i, ElmType &elm);
    bool pop_front();
    bool pop_front(ElmType &ch);
    bool push_front(int ch);
    bool pop_back(int &ch);

    int len() const {return len_;}
    int begin() const {return begin_;}
    int end() const {return end_;}
    bool print()
    {
#if 1
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
#endif
    }
    bool ready() const
    {
      //cout << "len_:" << len_ << endl;
      if (len_ > 1)
        return true;
      else
        return false;
    }
    bool full()
    {
      return (!can_push());
    }
    bool empty()
    {
      return (!can_pop());
    }
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
  private:
    ElmType q_[DEQUE_LEN];
    int len_;
    int begin_, end_;
    int begin_front_, end_front_;
};

//}
#endif
