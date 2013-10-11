#include "stm32.h"

#include <setjmp.h>

jmp_buf mark;

int main(void)
{
  int i=0;
  int ret = setjmp(mark);
  ++i;
  while(1)
  {
    i=10;
    longjmp(mark, 5);
  }
  return 0;
}
