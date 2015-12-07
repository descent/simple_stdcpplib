#ifndef BST_H
#define BST_H

#ifdef USE_OS
#include <cstdio>
#include <cstdlib>

#include <string>
#include <iostream>

using namespace std;
#else

#include "myiostream.h"
#include "k_stdio.h"
using namespace DS;

#endif

// GNode: G - generic
template <typename Key, typename Value>
struct GNode
{
  int e_;
  GNode *l_, *r_;
  Key k_;
  Value v_;
  ~GNode()
  {
    // cout << "~GNode" << endl;
  }
};

template <typename NodeType, typename Key, typename Value>
NodeType *make_node(const Key &k, Value v)
{
  //cout << sizeof(NodeType) << endl;
  //NodeType *n = (NodeType*)malloc(sizeof(NodeType));
  //(n->k_).string("abc");
  NodeType *n = new NodeType;
  if (n)
  {
    n->k_ = k;
    n->v_ = v;
    n->r_ = n->l_ = 0;
  }
  return n;
}

template <typename NodeType>
void free_node(NodeType *n)
{
  delete n;
}

template <typename NodeType, typename Key, typename Value>
NodeType *insert(NodeType *t, const Key &k, Value v)
{
  if (t==0)
    return make_node<NodeType>(k, v);
  else if (t->k_ > k)
         t->l_ = insert(t->l_, k, v);
       else
         t->r_ = insert(t->r_, k, v);
  return t;
}

template <typename NodeType, typename Key>
NodeType* del(NodeType *n, const Key &k)
{
  NodeType *p;

  if (n==0)
    return 0;
  if (n->k_ > k)
    n->l_ = del(n->l_, k);
  else if (n->k_ < k)
         n->r_ = del(n->r_, k);
       else
       {
         if (n->l_ == 0 && n->r_ == 0)
         {
           free_node(n);
           n = 0;
         }
         else if (n->l_) // it has left subtree
              {
	        for (p = n->l_; p->r_; p = p->r_);

	        n->k_ = p->k_;
	        n->v_ = p->v_;
	        n->l_ = del(n->l_, n->k_);
              }
              else // it has right subtree
              {
	        for (p = n->r_; p->l_; p = p->l_);

	        n->k_ = p->k_;
	        n->v_ = p->v_;
	        n->r_ = del(n->r_, n->k_);
              }
       }
  return n;
}

template <typename NodeType>
void print_tree(NodeType *t)
{
  if (t)
  {
    cout << "(" << t->k_;
    //printf("(%f", t->k_);
    print_tree(t->l_);
    print_tree(t->r_);
    cout << ")";
  }
  else
  {
    printf("()");
  }
}

#endif
