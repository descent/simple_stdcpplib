#include "mymap.h"


#ifdef TEST

#include <iostream>

using namespace DS;

int main(int argc, char *argv[])
{
  DS::map<int,int> mymap = {{100, 7}, {101, 5}};

  mymap.insert({3,21});
  mymap.insert({1,2});
  mymap.insert(DS::map<int,int>::value_type(13, 20));

  for (auto it = mymap.begin() ; it != mymap.end() ; ++it)
  {
    cout << it->k_ << endl;
    cout << it->v_ << endl;
  }
#if 1
  auto it = mymap.find(3);
  if (it != 0)
  {
    cout << "found 3:" << (*it).v_ << endl;
    it->v_ = 555;
  }
#endif
  for (auto it = mymap.begin() ; it != mymap.end() ; ++it)
  {
    cout << it->k_ << endl;
    cout << it->v_ << endl;
  }

  return 0;
}
#endif
