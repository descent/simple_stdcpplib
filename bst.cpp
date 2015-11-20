// from: linux c 編程 - 一站式學習 (p 432) 

#include <cstdio>
#include <cstdlib>

using namespace std;

struct Node
{
  int e_;
  Node *l_, *r_;
};

Node *make_node(int e)
{
  Node *n = (Node *)malloc(sizeof(Node));
  n->e_ = e;
  n->l_ = n->l_ = 0;

}

Node *insert(Node *t, int e)
{
  if (t==0)
    return make_node(e);
  else if (t->e_ > e)
         t->l_ = insert(t->l_, e);
       else
         t->r_ = insert(t->r_, e);

  return t;
}

void print_tree(Node *t)
{
  if (t)
  {
    printf("(%d", t->e_);
    print_tree(t->l_);
    print_tree(t->r_);
    printf(")");
  }
  else
  {
    printf("()");
  }
}

int main(int argc, char *argv[])
{
  Node *root = 0;

  root = insert(root, 3);
  root = insert(root, 1);
  root = insert(root, 10);
  root = insert(root, 9);
  root = insert(root, 2);
  root = insert(root, 8);
  root = insert(root, 4);
  root = insert(root, 5);

  printf("\\tree");
  print_tree(root);
  printf("\n");
  
  return 0;
}
