#ifndef BTREE_CPP
#define BTREE_CPP

struct Node
{
  int elm_;
  Node *l_, *r_;
};

Node *make_node(int elm);


#endif
