#include "mylist.h"

#ifdef TEST
int main(int argc, char *argv[])
{
  DS::vector<int> vec;  

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);
  for (int i=0 ; i < vec.length() ; ++i)
  {
    cout << vec[i] << endl;
  }
  cout << vec.max_size() << endl;

  return 0;
}
#endif
