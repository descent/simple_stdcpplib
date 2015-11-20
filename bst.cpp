// from: linux c 編程 - 一站式學習 (p 432) 

#include <cstdio>
#include <cstdlib>

#include <string>
#include <iostream>

using namespace std;

struct Node
{
  int e_;
  Node *l_, *r_;
  std::string k_;
  int v_;
};

Node *make_node(int e)
{
  Node *n = (Node *)malloc(sizeof(Node));
  n->e_ = e;
  n->l_ = n->l_ = 0;
}

Node *make_node(const std::string &k, int v)
{
  Node *n = (Node *)malloc(sizeof(Node));
  n->k_ = k;
  n->v_ = v;
  n->l_ = n->l_ = 0;
}

Node *insert(Node *t, const std::string &k, int v)
{
  if (t==0)
    return make_node(k, v);
  else if (t->k_ > k)
         t->l_ = insert(t->l_, k, v);
       else
         t->r_ = insert(t->r_, k, v);

  return t;
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
    cout << "(" << t->k_;
    print_tree(t->l_);
    print_tree(t->r_);
    printf(")");
  }
  else
  {
    printf("()");
  }
}

void test_1()
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
}

Node *search (Node *n, const std::string &k)
{
  if (n==0)
    return 0;
  if (n->k_ > k)
    return search(n->l_, k);
  if (n->k_ < k)
    return search(n->r_, k);

  return n; // n->k_ == k
}

int main(int argc, char *argv[])
{
  Node *root = 0;
  root = insert(root, "abc", 3);
  root = insert(root, "def", 1);
  root = insert(root, "xyz", 10);
  printf("\\tree");
  print_tree(root);
  printf("\n");

  string str("adef");
  Node *n = search(root, str);
  if (n==0)
    cout << "not found: " << str << endl;
  else
    cout << "found (" << n->k_ << ", " <<  n->v_<< ")" << endl;
  
  return 0;
}
