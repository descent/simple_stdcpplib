/* ENTRY(main) */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 128K
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 192K

}

SECTIONS
{
  .text :
  {
    KEEP(*(.isr_vector))
    *(.text)
    *(.text.*)
    *(.rodata)
    *(.rodata.*)
    __start_global_ctor__ = .;
    *(.init_array)
    __end_global_ctor__ = .;
    _etext = .;
    _sidata = .;
  } >FLASH



  /* Initialized data will initially be loaded in FLASH at the end of the .text section. */
  /* .data : AT(0x5000) */
  .data : AT(_sidata) 
  {
    _data = .;

    _sdata = .;

    *(.data)		/* Initialized data */
    _edata = .;
  } >RAM

  .myheap (NOLOAD):
  {
    . = ALIGN(8);
    *(.myheap)
    . = ALIGN(8);
  } >RAM

  .bss : 
  {
    _bss = .;
    _sbss = .;
    *(.bss)         /* Zero-filled run time allocate data memory */
    _ebss = .;
  } >RAM

    
  _estack = ORIGIN(RAM) + LENGTH(RAM);
}  
