#ifndef MYLIST_H
#define MYLIST_H

#include "type.h"

#ifdef USE_OS
#include <iostream>
using namespace std;
#else
#include "myiostream.h"
#include "mem.h"
#endif

namespace DS
{

  template <typename Type>
  struct Node
  {
    Type e_;
    Node *f_, *r_;
  };

  template <typename Type>
  struct list
  {
    public:
      list();
      ~list();

// from: http://stackoverflow.com/questions/8164567/how-to-make-my-custom-type-to-work-with-range-based-for-loops
   class iterator {
   public:
     iterator(Node<Type> * p){ptr = p;}
     iterator operator++() {ptr=ptr->r_ ; return *this;}// iterator i(ptr); ptr = ptr->r_; return i; }
     bool operator!=(const iterator & other) {return (ptr != 0);}// return ptr != other.ptr; }
     const Type& operator*() const {return ptr->e_;}
   private:
     Node<Type>* ptr;
   };
      void push_back (const Type& val);
      u32 length() const {return len_;}
      //Type* begin(){return head_;}
      //Type* end(){return 0;}
      iterator begin() const { return iterator(head_); }
      iterator end() const { return iterator(tail_->r_); }
      Node<Type> *head_;
      Node<Type> *tail_;

    private:
      u32 len_;

  };

}

template <typename Type>
DS::list<Type>::list():len_(0), head_(0), tail_(0)
{
  printf("list ctor\r\n");
  //data_ = new Type[VEC_DEFAULT_LEN];
  //max_len_ = VEC_DEFAULT_LEN;
}

template <typename Type>
DS::list<Type>::~list()
{
  printf("list dtor\r\n");
  Node<Type> *n;

  for (n = head_ ; n ; n=n->r_)
    delete n;
}

template <typename Type>
void DS::list<Type>::push_back (const Type& val)
{
  Node<Type> *n = new Node<Type>;
  n->e_ = val;
  n->f_ = n->r_ = 0;
  if (head_ == 0)
  {
    head_ = n;
  }
  else
  {
    tail_->r_ = n;
  }
  tail_ = n;
  //cout << "head_: " << hex << (u32 *)head_ << endl;
  //cout << "tail_: " << hex << (u32*)tail_ << endl << dec;
  ++len_;
}

#endif
