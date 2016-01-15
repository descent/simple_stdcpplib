#include "mylist.h"

#ifdef TEST_MAIN
class Composite1
{
  public:
    Composite1()
    {
      printf("Composite1\n");
    }
};

class Composite2
{
  public:
    Composite2()
    {
      printf("Composite2\n");
    }
};

class CompositeObj
{
  public:
    CompositeObj()
    {
      printf("CompositeObj\n");
    }
  private:
    Composite1 c1_;
    Composite2 c2_;
};
int main(int argc, char *argv[])
{
  CompositeObj *co;

  // co = new CompositeObj{};
  // co = (CompositeObj*)malloc(sizeof(CompositeObj));

  DS::list<int> list;  

  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);
  for (auto it=list.begin() ; it != list.end() ; ++it)
  {
    cout << *it << endl;
  }
  #if 0
  for (int i=0 ; i < list.length() ; ++i)
  {
    cout << vec[i] << endl;
  }
  cout << vec.max_size() << endl;
  #endif

  return 0;
}
#endif
