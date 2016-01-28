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
  call ResetISR


LABEL_STACK:
  .space 10240, 0
  .set top_of_stack, (. - LABEL_STACK)
