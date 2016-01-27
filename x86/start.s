.code16
.section booting
.global begin
begin:
  mov %cs,%ax
  mov %ax,%ds
  mov %ax,%es
  mov %ax, %ss
  mov $0xff00, %sp

  movw    $0xb800, %ax
  movw    %ax, %gs

  call enter_main

