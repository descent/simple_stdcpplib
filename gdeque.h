/*
 * g: generic
 * gdeque: generic deque
 */

#ifndef GDEQUE_H
#define GDEQUE_H


//#define USE_NCURSES

#ifdef OS_CPP
#ifdef USE_NCURSES
  #include <ncurses.h>
#else
  #include <iostream>
  using namespace std;
#endif

#else

#endif

namespace DS
{

//const int DEQUE_LEN = 32;

template <typename ElmType, int deque_size=32>
class Deque
{
  public:
    explicit Deque()
    {
      init();
    }


    bool push_back(ElmType &ch)
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

    bool back(int i, ElmType &elm)
    {
      if (ready() == false) 
        return false;
      if (i < 0 || i >= size())
        return false;

      bool ret = true;

      int b = ((begin_ - i + len_) % len_);

      if (b == end())
      {
        ret = false;
      }
      else
      {
        elm = *(q_ + (b - 1 + len_) % len_);
      }
      return ret;
    }
    bool pop_front()
    {
      ElmType ch;
      return pop_front(ch);
    }
    bool pop_front(ElmType &ch)
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

    bool push_front(ElmType ch)
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

    bool pop_back(ElmType &ch)
    {
      if (ready() == false) 
        return false;

      bool ret = true;
      if (can_pop())
      {
        begin_ = ((begin_ - 1 + len_) % len_);
        ch = *(q_ + begin_);
      }
      else
      {
        ret = false;
      }
      return ret;
    }
    bool pop_back()
    {
      ElmType elm; 
      return pop_back(elm);
    }

    int len() const {return len_;}
    int begin() const {return begin_;}
    int end() const {return end_;}
    bool print()
    {
#ifdef OS_CPP
      cout << "begin: " << begin_ << endl;
      cout << "end: " << end_ << endl;
      if (ready() == false) return false;
      cout << "-- ";
      int e = end();
      for (int i=e ; i != begin() ; )
      {
        ElmType e = *(q_ + i);
        //cout << *(q_ + i) << " ";
        cout << e.c_str() << " ";
        i = (i + 1) % len_;
      }
      cout << " --" << endl;
      return true;
#endif
#ifdef USE_NCURSES
      mvprintw(0, 40, "begin: %d", begin_);
      mvprintw(1, 40, "end: %d", end_);
      if (ready() == false) return false;
      int e = end();

      int j=2;
      for (int i=e ; i != begin() ; )
      {
        ElmType s = *(q_ + i);
        mvprintw(j++, 40, s.c_str());
        i = (i + 1) % len_;
      }
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
    int size() const
    {
      if (begin_ >= end_)
      {
        return begin_ - end_;
      }
      else
      {
        return len_ - end_ + begin_;
      }
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
    void clear()
    {
      init();
    }
  private:
    void init()
    {
      len_ = deque_size;
      begin_ = end_ = 0;
    }
    ElmType q_[deque_size];
    int len_;
    int begin_, end_;
    int begin_front_, end_front_;
};

} // end namespace DS
#endif
