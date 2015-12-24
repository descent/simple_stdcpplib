#ifndef MYMAP_H
#define MYMAP_H

#include "type.h"
#include "bst.h"
#include "initializer_list"

#ifdef USE_OS
#include <iostream>
using namespace std;
#else
#include "myiostream.h"
#include "myvec.h"
#include "mem.h"
#endif

namespace DS
{
  template <typename Key, typename Value>
  class map
  {
    public:
      typedef GNode<Key, Value> value_type;


      #if 0
      void insert(std::initializer_list<value_type> __list)
      { 
      //insert(__list.begin(), __list.end()); 
      }
      #endif



      class iterator 
      {
        public:
          iterator(vector<GNode<Key, Value> *> *it):it_(it), index_(0)
          {}
          iterator operator++() {++index_; return *this;}
          bool operator!=(const iterator & other) {return index_ != other.it_->length();}
          GNode<Key, Value> operator*(){return *((*it_)[index_]);}
          GNode<Key, Value>* operator->(){return (*it_)[index_];}
        private:
          vector<GNode<Key, Value>*>* it_;
          int index_;
          int end_;
      };

      iterator find(const Key& k) 
      { 
        //GNode<Key, Value> *n = search(root_, k);
      // return _M_t.find(__x); 
      }

      map();
      map(std::initializer_list<value_type> list)
      {
        for (auto it = list.begin(); it != list.end() ; ++it)
          insert(*it);
      }
      ~map();

      iterator begin()
      { 
        in_order(root_);
        return iterator(&it_order_);
      }
      iterator end() 
      { 
        return iterator(&it_order_);
      }

      void insert(const value_type& node)
      {
        root_ = ::insert(root_, node.k_, node.v_);
      }


#if 0
      void insert(const Key &k, const Value v)
      {
        root_ = ::insert(root_, k, v);
      }
#endif
      Value& operator[](Key key)
      {
        GNode<Key, Value> *n = search(root_, key);
        if (n)
          return n->value_;
        else
          return 0;
      }

      void in_order(GNode<Key, Value> *n)
      {
        if (n == 0)
          return;
        in_order(n->l_);
        it_order_.push_back(n);
        in_order(n->r_);
      }

      vector<GNode<Key, Value> *> it_order_;
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
