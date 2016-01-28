#ifndef BIOS_CALL_H
#define BIOS_CALL_H

//#ifdef X86_16
  __asm__(".code16gcc\n");
  //__asm__(".code16\n");
//#endif

#include "../type.h"

extern "C" 
{
  void bios_print_char(u8 ch);
}
void bios_print_str(const u8 *str, int len);

#endif
