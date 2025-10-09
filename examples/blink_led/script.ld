ENTRY(_Reset)

SECTIONS
{
  . = 0xC0300000;



  .text   : ALIGN(4) { *(.text*) }
  .rodata : ALIGN(4) { *(.rodata*) }
  .data   : ALIGN(4) { *(.data*) }
  .bss (NOLOAD) : ALIGN(4) { *(.bss*) *(COMMON) }

  /* _stack_top = 0xC0500000; */
}
