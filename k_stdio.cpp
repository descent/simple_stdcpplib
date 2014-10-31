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

MyDeque mydeque;

int ungetch(int c)
{
#if 0
  myprint("\r\nun: ");
  myprint(c);
  myprint("\r\n");
  keep_char = c;
#endif
  mydeque.push_front(c);
  return 0;
}

int read_char()
{
  while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
  return (USART_ReceiveData(USART2) & 0x7F);
}

int getchar()
{
  int b;

  if (mydeque.empty())
  {
    while(1)
    {

    b = read_char();

    switch (b)
    {
      case 0x8: // backspace
      {
        if (mydeque.empty())
          break;

        send_byte(b);
        send_byte(' ');
        send_byte(b);
        mydeque.pop_back(b);
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
        if (b == '\r') // enter
        {
          myprint("\r\n");
          mydeque.push_back(b);
          goto end;
        }
        else
          send_byte(b);

        mydeque.push_back(b);
        break;
      }
    }
      if (mydeque.full())
        break;
    }

  }

end:
    int ch;
    mydeque.pop_front(ch);
    return ch;

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
      case 0x8: // backspace
      {
        send_byte(b);
        send_byte(' ');
        send_byte(b);
        return getchar();
        //break;
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
