.code16
.section booting
.global begin
begin:
  mov %cs,%ax
  mov %ax,%ds
  mov %ax,%es


  #mov $0x8000,%ax
  mov %ax, %ss
#  mov $0xfff0, %esp
  mov $top_of_stack, %esp
  xchg %bx, %bx

  movw    $0xb800, %ax
  movw    %ax, %gs

#  call enter_main
  callw ResetISR

#ref: http://www.cppblog.com/luqingfei/archive/2011/06/13/122220.html
.global bios_read_char
bios_read_char:
  mov 0x0, %ah
  int $0x16
  mov 0x0, %ah
  retl

.global bios_print_char
bios_print_char:
    pushl   %eax
    pushl   %ebx
    mov     $0x0e,%ah
    mov     0x4(%esp), %al    /* Char to print */
    mov     $0x0f, %bl   /* Front color: white */
    int     $0x10       /* BIOS int 10h, ah=0xe: Print char */
    popl   %ebx
    popl   %eax
    retl

LABEL_STACK:
  .space 10240, 0
  .set top_of_stack, (. - LABEL_STACK)
