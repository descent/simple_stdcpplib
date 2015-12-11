#ifndef MYMAP_H
#define MYMAP_H

#include "type.h"
#include "bst.h"

#ifdef USE_OS
#include <iostream>
using namespace std;
#else
#include "myiostream.h"
#include "mem.h"
#endif

namespace DS
{
  template <typename Key, typename Value>
  struct map
  {
    public:

      class iterator 
      {
        public:
          iterator(GNode<Key, Value> * p){ptr_ = p;}
          iterator operator++() {}
          bool operator!=(const iterator & other) {}
          const GNode<Key, Value>& operator*() const {return ptr_;}
        private:
          GNode<Key, Value>* ptr_;
      };

      map();
      ~map();

      iterator begin() const 
      { 
        return iterator(root_); 
      }
      iterator end() const { return iterator(root_); }

      void insert(const Key &k, const Value v)
      {
        root_ = ::insert(root_, k, v);
      }
      Value& operator[](Key key)
      {
        GNode<Key, Value> *n = search(root_, key);
        if (n)
          return n->value_;
        else
          return 0;
      }
    private:
      GNode<Key, Value> *root_;
  };

}

template <typename Key, typename Value>
DS::map<Key, Value>::map():root_(0)
{
  printf("map ctor\r\n");
}

template <typename Key, typename Value>
DS::map<Key, Value>::~map()
{
  printf("map dtor\r\n");
  // delete all node
}


#endif
