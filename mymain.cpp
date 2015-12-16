#include "myiostream.h"

using namespace DS;



typedef int (*InitFunc)(void);


int init_timer(void)
{
  return 0;
}

static InitFunc init[]=
{
  init_timer,
  //ramdisk_driver_init,
  //romfs_init,
  //mm_init,
  0
};

void load_init_boot(InitFunc *init_func)
{
  for (int i = 0 ; init_func[i] ; ++i)
  {
    init_func[i]();
  }
}

void plat_boot(void)
{
  load_init_boot(init);
}

int mymain()
{
  char *c = new char;
  cout << "abc" << endl;
}
