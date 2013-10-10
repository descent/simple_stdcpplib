#include <stdio.h>
#include <stdlib.h>

#include "my_setjmp.h"

jmp_buf mark;

int main(int argc, char *argv[])
{
  int ret = my_setjmp(mark);
  printf("ret: %d\n", ret);
  if (ret == 0)
  {
    printf("init setjmp\n");
  }
  else
  {
    printf("exit ret: %d\n", ret);
    exit(0);
  }
  printf("xxx\n");
  my_longjmp(mark, 6);
  //longjmp(mark, 1);
  return 0;
}
