#define USE_STDPERIPH_DRIVER

#include "stm32f10x.h"
#include "stm32_p103.h"

#include "bst.h"
#include "mem.h"

#if 0
#include "k_stdio.h"
#include "s_eval.h"
#include "gdeque.h"
#include "cstring.h"
#endif

// using namespace DS;

uint8_t get_byte()
{
  while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);

  return (USART_ReceiveData(USART2) & 0x7F);
}

#if 0
void myfree(void *ptr)
{
}

void *mymalloc(int size)
{
  static char mem[256];
  return mem;
}
#endif

void *operator new(unsigned int s)
{
  return mymalloc(s);
}

void operator delete(void *p)
{
  myfree(p);
}


extern "C"
{

int main(void)
{
  int val=98;
  init_rs232();
  USART_Cmd(USART2, ENABLE);

  printf("test bst: %d\r\n", val);

  GNode<int, int> *root = 0;

  root = insert(root, 8, 7);
  root = insert(root, 4, 7);
  root = insert(root, 14, 7);

  print_tree(root);
  while(1);

  return 0;

}

}
