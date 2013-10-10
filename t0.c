#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf mark;

int main(int argc, char *argv[])
{
  int ret = setjmp(mark);
  printf("ret: %d\n", ret);
  if (ret == 0)
  {
    printf("init setjmp\n");
  }
  else
  {
    printf("exit\n");
    exit(0);
  }
  printf("xxx\n");
  longjmp(mark, 5);
  //longjmp(mark, 1);
  return 0;
}
