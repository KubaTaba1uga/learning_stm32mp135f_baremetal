ENTRY(_Reset) /* Specify entry function of a program */
OUTPUT_FORMAT("elf32-littlearm")  /* Specify output architecture of the host */

MEMORY {
  /* Name   Permissions   Starting address          Size */
     RAM    (rwx):        ORIGIN = 0xC0000000 + 3M, LENGTH = 0xD9F20000 - 0xC0000000 - 3M
  /* We start at 3MB offset because tf-a, optee and uboot need some space at the beginning
     of RAM, i took it from other STM32MP13 baremetal projects.
   */      
}

SECTIONS {
     .text : ALIGN(4) {        /* Align section to 4 bytes (32bits). */
             _TEXT_START_ = .; /* Specify symbols wich can be used as guard to detect where */
             *(.text)          /* .text section starts and where it ends. */
             _TEXT_END_ = .;	     
     } > RAM /* Put section in RAM memory region */

     .data : ALIGN(4) {   
             _DATA_START_ = .;
             *(.data)
             _DATA_END_ = .;	     
     } > RAM

     .bss (NOLOAD) : ALIGN(4) {   /* Does not allocate memory for this region in binary */
             _BSS_START_ = .;     /* and do not load this memory region from binary. */
             *(.bss)         
             _BSS_END_ = .;	     
     } > RAM

     /* Declare as big heap as possible */
     HEAP_SIZE = LENGTH(RAM) - SIZEOF(.text) - SIZEOF(.data) - SIZEOF(.bss) - SIZEOF(.stack) - 16;
     .heap (NOLOAD) : ALIGN(16) {
       _HEAP_START_ = .;
       . = . + HEAP_SIZE; /* Heap grows upwords so we want to allocate it at the beggining of available RAM. */
       _HEAP_END_ = .;
     }

     /* Declare 8MB stack */
     STACK_SIZE = 8M;
     . = ORIGIN(RAM) + LENGTH(RAM) - STACK_SIZE;
     .stack (NOLOAD) : ALIGN(16)
     {
	       _STACK_END_ = .;
	       . = . + STACK_SIZE;  /* Stack grows downwords so we want to allocate it at the end of RAM. */
	       _STACK_START_ = .; 
     } > RAM
}
