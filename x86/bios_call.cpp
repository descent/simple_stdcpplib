
void bios_print_char(char ch)
{
}

void bios_print_str(const char *str, int len)
{

  __asm__ __volatile__
  (
    "push %%bp\n"
    "push %%cx\n"
    "push %%ax\n"
    "push %%bx\n"
    "push %%dx\n"
    "mov %0, %%bp\n"   // ES:BP = 串位址
    "mov %1, %%cx\n"   // CX = 串長度
    "mov 0x01301, %%ax\n"  // AH = 13,  AL = 01h
    "mov $0x000c, %%bx\n"  // 頁號為 0(BH = 0) 黑底紅字 (BL = 0Ch, 高亮)
    "mov $0, %%dl\n"
    "int $0x10\n"
    "pop %%dx\n"
    "pop %%bx\n"
    "pop %%ax\n"
    "pop %%cx\n"
    "pop %%bp\n"
    :
    :"g"(str), "g"(len)
    :
  );
}
