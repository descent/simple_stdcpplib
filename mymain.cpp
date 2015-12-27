#include "myiostream.h"

using namespace DS;

int mymain()
{
  int i=0;
  for (i=0 ; i < 100 ; ++i)
  {
    char *c = new char;
    cout << "i: " << i << endl;
  }
  cout << "abc" << endl;
}
