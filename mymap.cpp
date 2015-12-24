#include "mymap.h"


#ifdef TEST

#include <iostream>

using namespace DS;

int main(int argc, char *argv[])
{
  DS::map<int,int> mymap = {{100, 7}, {101, 5}};

  mymap.insert({3,21});
  mymap.insert({1,2});

  for (auto it = mymap.begin() ; it != mymap.end() ; ++it)
  {
    cout << it->k_ << endl;
  }
#if 1
  auto it = mymap.find(3);
  if (it != 0)
  {
    cout << "found 3" << endl;
  }
#endif

  return 0;
}
#endif
