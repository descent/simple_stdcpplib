.code16
.section booting
.global begin
begin:
  mov %cs,%ax
  mov %ax,%ds
  mov %ax,%es
  mov %ax, %ss
  mov $top_of_stack, %esp
  xchg %bx, %bx

  movw    $0xb800, %ax
  movw    %ax, %gs

#  call enter_main
  callw ResetISR


.global bios_print_char
bios_print_char:
    mov     $0x0e,%ah
    mov     0x4(%esp), %al    /* Char to print */
    mov     $0x0f, %bl   /* Front color: white */
    int     $0x10       /* BIOS int 10h, ah=0xe: Print char */
    ret

LABEL_STACK:
  .space 40960, 0
  .set top_of_stack, (. - LABEL_STACK)
