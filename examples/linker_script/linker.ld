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

/* ENTRY(_reset); */
/* MEMORY { */
/*   dram(rwx) : ORIGIN = 0xC0000000, LENGTH = 128k */
/* } */
/* _estack     = ORIGIN(dram) + LENGTH(dram);    /\* stack points to end of DRAM *\/ */

/* SECTIONS { */
/*   .text     : { *(.text*) }                   > dram */
/*   .rodata   : { *(.rodata*) }                 > dram */
/*   /\* .data     : { *(.data SORT(.data.*)) }      > dram *\/ */
/*   /\* .bss      : { *(.bss SORT(.bss.*) COMMON) } > dram *\/ */
/*   /\* . = ALIGN(8); *\/ */
/*   /\* _end = .;     /\\* for cmsis_gcc.h  *\\/ *\/ */
/* } */
