#ifndef BTREE_CPP
#define BTREE_CPP

#ifdef X86_16
  __asm__(".code16gcc\n");
#endif

struct Node
{
  int elm_;
  Node *l_, *r_;
};

Node *make_node(int elm);


#endif
