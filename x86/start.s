.code16

# if specify 0x8000 to ds, ss, es
# need copy data segment from 0x9000:data_addr to 0x8000:data_addr
# init_data_asm function handes the part.
# linker script needs put rodata section to data section
# like this:
#
#  .data :
#  {
#    _data = .;
#
#    _sdata = .;
#    *(.ccm)
#    *(.rodata)
#    *(.rodata.*)
#
#    *(.data)            /* Initialized data */
#    _edata = .;
#  }
# but still need some c runtime code, current I don't known what needs,
# only note current status.

.extern _sdata
.extern _edata

.section booting
.global begin
begin:
  mov %cs,%ax
  mov $0x8000,%ax
  mov %ax,%ds
  mov %ax,%es
  mov %ax, %ss
  mov $0xfff0, %esp

  call init_data_asm

#  mov $top_of_stack, %esp
  xchg %bx, %bx

  movw    $0xb800, %ax
  movw    %ax, %gs

#  call enter_main
  callw ResetISR

#ref: http://www.cppblog.com/luqingfei/archive/2011/06/13/122220.html
.global bios_read_char
bios_read_char:
#  mov 0x0, %ah
  xor %ax, %ax
  int $0x16
  mov 0x0, %ah
  retl

.global back_to_dos
back_to_dos:
  mov     $0x4c00, %ax
  int     $0x21             #  回到 DOS

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


# init data section
init_data_asm:
  movw $_edata, %di    /* Destination */
  movw $_sdata, %si   /* Source */
#  movw $0x0, %ax
#  movw %ax, %gs
  jmp 2f
1:
  mov $0, %eax
  movw %si, %ax
#  movb $0x1, (%eax)
  movb %cs:(%eax), %bl
  movb %bl, %ds:(%eax)
  add $1, %si

2:
  cmpw %di, %si
  jne 1b
  ret
#LABEL_STACK:
#  .space 10240, 0
#  .set top_of_stack, (. - LABEL_STACK)

asm_memcpy:
    pushl   %ebp
    mov     %esp, %ebp

    pushl   %esi
    pushl   %edi
    pushl   %ecx

    mov $0x7000, %ax
    mov %ax, %fs

    mov     8(%ebp), %edi    /* Destination */
    mov     12(%ebp), %esi   /* Source */
    mov     16(%ebp), %ecx   /* Counter */
MemCpy.1:
    cmp     $0, %ecx  /* Loop counter */
    jz      MemCpy.2
    movb    %ds:(%esi), %al
    inc     %esi
    movb    %al, %fs:(%edi)
    inc     %edi
    dec     %ecx
    jmp     MemCpy.1
MemCpy.2:
    mov     8(%ebp), %eax
    pop     %ecx
    pop     %edi
    pop     %esi
    mov     %ebp, %esp
    pop     %ebp
    ret
