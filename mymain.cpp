#include "myiostream.h"
#include "myvec.h"
#include "mymap.h"
#include "mystring.h"
#include "mylist.h"

using namespace DS;

class BaseClass
{
  public:
    BaseClass(int base=5): base_(base)
    {
      cout << "BaseClass: " << base_ << endl;
    }
    virtual void vfunc()
    {
      cout << "Base vfunc: " << base_ << endl;
    }
  private:
    int base_;
};

class DeriveClass : public BaseClass
{
  public:
    DeriveClass(int d=10): BaseClass(99), d_(d)
    {
      cout << "DeriveClass: " << d_ << endl;
    }
    virtual void vfunc()
    {
      cout << "derive vfunc: " << d_ << endl;
    }
  private:
    int d_;
};

int mymain()
{

#if 1
  BaseClass *bc = new BaseClass(1);
  DeriveClass *dv = new DeriveClass(2);

  cout << "call bc->vfunc();" << endl;
  bc->vfunc();

  bc = dv;
  cout << "call dv->vfunc();" << endl;
  bc->vfunc();
#endif

  int i=0;

{
  vector<string> vec;

  vec.push_back("abc");
  vec.push_back("xyz");
  vec.push_back("123");
  vec.push_back("abcdefghijk!@#$%^&*()");

  for (i=0 ; i < vec.size() ; ++i)
    cout << vec[i] << endl;
  cout << "test vec iterator" << endl;
  for (auto it=vec.begin() ; it!=vec.end() ; ++it)
    cout << *it << endl;
}

{
  map<string, int> str_map;

  str_map.insert({"zxcv", 5});
  str_map.insert({"abc", 51});
  str_map.insert({"abcdefghqq", 151});
  str_map.insert({"111", 99});

  for (auto it=str_map.begin() ; it!=str_map.end() ; ++it)
    cout << "(" << it->k_ << "," << it->v_ << ")" << endl;

}

{
  list<string> list;

  list.push_back("xyz");
  list.push_back("123");
  list.push_back("qwerty");
  cout << "test list" << endl;
  for (auto it=list.begin() ; it!=list.end() ; ++it)
    cout << *it << endl;
}
  for (i=0 ; i < 100 ; ++i)
  {
    char *c = new char;
    cout << "i: " << i << endl;
  }
  cout << "abc" << endl;
}
