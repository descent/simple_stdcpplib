/*
 * binary tree
 */
#include "btree.h"

#include <cstdlib>
#include <cstdio>

using namespace std;

Node *make_node(int elm)
{
  Node *n = (Node*)malloc(sizeof(Node));
  if (n)
  {
    n->elm_ = elm;
    n->r_ = 0;
    n->l_ = 0;
  }

  return n;
}

typedef void (*Fp)(Node *n);

void print_node(Node *n)
{
  printf("%d, ", n->elm_);
}

void pre_order(Node *n, Fp fp)
{
  if (n == 0)
    return;
  fp(n); 
  pre_order(n->l_, fp);
  pre_order(n->r_, fp);
}

void in_order(Node *n, Fp fp)
{
  if (n == 0)
    return;
  in_order(n->l_, fp);
  fp(n); 
  in_order(n->r_, fp);
}


#if 0

                  1
                /   \
               2     3
              / \   / \
             4   5 6   7

#endif

int main(int argc, char *argv[])
{
  Node *n1 = make_node(1); 
  Node *n2 = make_node(2); 
  Node *n3 = make_node(3); 
  Node *n4 = make_node(4); 
  Node *n5 = make_node(5); 
  Node *n6 = make_node(6); 
  Node *n7 = make_node(7); 

  n1->r_ = n3;
  n1->l_ = n2;

  n2->r_ = n5;
  n2->l_ = n4;

  n3->r_ = n7;
  n3->l_ = n6;

  printf("pre order:\n");
  pre_order(n1, print_node);
  printf("\n");

  printf("in order:\n");
  in_order(n1, print_node);
  printf("\n");

  return 0;
}
