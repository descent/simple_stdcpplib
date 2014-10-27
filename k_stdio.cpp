#include "k_stdio.h"
#include "k_string.h"

#include "stm32f4xx_usart.h"

void send_byte(u8 b)
{
  /* Send one byte */
  USART_SendData(USART2, b);

  /* Loop until USART2 DR register is empty */
  while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

void myprint(const char *str)
{
  const char *p = str;
  while(*p)
    send_byte(*p++);
}

void myprint(int num)
{
  char str[10];
  s32_itoa_s(num, str, 10);
  myprint(str);
}

int keep_char = -1;

int ungetch(int c)
{
#if 0
  myprint("\r\nun: ");
  myprint(c);
  myprint("\r\n");
#endif
  keep_char = c;
  return 0;
}

int getchar()
{
  int b;

  if (keep_char != -1 )
  {
    b = keep_char;
    keep_char = -1;
    return b;
  }
  else
  {
    while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
    b = (USART_ReceiveData(USART2) & 0x7F);
    switch (b)
    {
      case '\r': // press enter
      {
        myprint("\r\n");
        break;
      }
#if 0
      case '\n':
      {
        break;
      }
#endif
      default:
      {
        send_byte(b);
        break;
      }
    }
    return b;
  }
}
