// from: linux c 編程 - 一站式學習 (p 432) 

#include <cstdio>
#include <cstdlib>

#include <string>
#include <iostream>

using namespace std;

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
    cout << "~GNode" << endl;
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

template <typename NodeType>
void print_tree(NodeType *t)
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


template <typename NodeType, typename Key>
NodeType *search (NodeType *n, const Key &k)
{
  if (n==0)
    return 0;
  if (n->k_ > k)
    return search(n->l_, k);
  if (n->k_ < k)
    return search(n->r_, k);

  return n; // n->k_ == k
}

void test_1()
{
#if 0
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
#endif
}

void test_2()
{
#if 0
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
#endif
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

template <typename NodeType>
NodeType* invert_tree(NodeType* root) 
{
  NodeType *tmpNode;

  if (root) 
  {
    tmpNode = root->l_;
    root->l_ = invert_tree(root->r_);
    root->r_ = invert_tree(tmpNode);
  }

  return root;
}

int main(int argc, char *argv[])
{
  GNode<std::string, int> *root = 0;
  root = insert(root, "abc", 3);
  root = insert(root, "def", 1);
  root = insert(root, "xyz", 10);
  root = insert(root, "lmn", 987);
  printf("\\tree");
  print_tree(root);
  printf("\n");

  string str("def");
  GNode<std::string, int> *n = search(root, str);
  if (n==0)
    cout << "not found: " << str << endl;
  else
    cout << "found (" << n->k_ << ", " <<  n->v_<< ")" << endl;

  GNode<double, int> *r1 = 0;
  r1 = insert(r1, 1.2, 3);
  r1 = insert(r1, 3.2, 5);
  r1 = insert(r1, 2.2, 4);
  r1 = insert(r1, 5.2, 7);
  r1 = insert(r1, 5.8, 0);
  printf("\\tree");
  print_tree(r1);
  printf("\n");

  GNode<double, int> *r2 = 0;

  r2 = invert_tree(r1);

  printf("\n\n");
  printf("\\tree");
  print_tree(r2);
  printf("\n");

  return 0;
}
