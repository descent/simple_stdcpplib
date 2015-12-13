#ifndef MYVEC_H
#define MYVEC_H

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
  const int VEC_DEFAULT_LEN=1;

  template <typename Type>
  struct vector
  {
    public:
      vector();
      ~vector();
      Type& operator[](unsigned int idx){return data_[idx];}
      void push_back (const Type& val);
      u32 length() const {return len_;}
      u32 max_size() const {return max_len_;}
    private:
      void grow();
      Type *data_;
      u32 len_;
      u32 max_len_;
  };

}

template <typename Type>
DS::vector<Type>::vector():len_(0), data_(0), max_len_(0)
{
  //data_ = new Type[VEC_DEFAULT_LEN];
  //max_len_ = VEC_DEFAULT_LEN;
}

template <typename Type>
DS::vector<Type>::~vector()
{
  delete [] data_;
}

template <typename Type>
void DS::vector<Type>::push_back (const Type& val)
{
  if (len_ >= max_len_)
  {
    grow();
  }
  data_[len_] = val;
  ++len_;
}

template <typename Type>
void DS::vector<Type>::grow()
{
  //cout << "grow max_len: " << max_len_ << endl;
  if (max_len_ == 0)
    max_len_ = 1;
  else
    max_len_ *= 2; // note overflow u32
  //cout << "after grow max_len: " << max_len_ << endl;
  Type *tmp = new Type[max_len_];
  //print_memarea();
  for (int i=0 ; i < len_ ; ++i)
    tmp[i] = data_[i];
  delete [] data_;
  //print_memarea();
  //cout << "===" << endl;
  data_ = tmp;
}

#endif
