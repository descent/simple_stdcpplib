#ifndef BIOS_CALL_H
#define BIOS_CALL_H

#ifdef X86_16
  __asm__(".code16gcc\n");
#endif

void bios_print_char(char ch);
void bios_print_str(const char *str, int len);

#endif
