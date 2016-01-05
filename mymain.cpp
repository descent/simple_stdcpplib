#include "myiostream.h"
#include "myvec.h"
#include "mymap.h"
#include "mystring.h"

using namespace DS;

int mymain()
{
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

  for (i=0 ; i < 100 ; ++i)
  {
    char *c = new char;
    cout << "i: " << i << endl;
  }
  cout << "abc" << endl;
}
