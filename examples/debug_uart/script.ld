ENTRY(_Reset)

SECTIONS
{
  . = 0xC0300000;

  .vector_table : ALIGN(0x20) { KEEP(*(.vector_table)) }
  .text : ALIGN(4) { *(.text*) }
  .rodata : ALIGN(4) { *(.rodata*) }
  .data   : ALIGN(4) { *(.data*) }
  .bss (NOLOAD) : ALIGN(4) { *(.bss*) *(COMMON) }
}
