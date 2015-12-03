#define USE_STDPERIPH_DRIVER

#include "stm32f10x.h"
#include "stm32_p103.h"
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

u8 buf[20];


extern "C"
{

int main(void)
{
  init_rs232();
  USART_Cmd(USART2, ENABLE);

  return 0;

}

}
