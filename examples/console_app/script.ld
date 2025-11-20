ENTRY(_Reset)
OUTPUT_FORMAT("elf32-littlearm")

MEMORY {
  /* Name   Permissions   Starting address          Size */
     RAM    (rwx):        ORIGIN = 0xC0000000 + 3M, LENGTH = 0xD9F20000 - 0xC0000000 - 3M
}

SECTIONS {
     .text : ALIGN(4) {        
             _TEXT_START_ = .; 
             *(.text)          
             _TEXT_END_ = .;	     
     } > RAM 

     .data : ALIGN(4) {   
             _DATA_START_ = .;
             *(.data)
             *(.rodata)	     
             _DATA_END_ = .;	     
     } > RAM

     .bss (NOLOAD) : ALIGN(4) {
             _BSS_START_ = .;  
             *(.bss)         
             _BSS_END_ = .;	     
     } > RAM

     HEAP_SIZE = LENGTH(RAM) - SIZEOF(.text) - SIZEOF(.data) - SIZEOF(.bss) - SIZEOF(.stack) - 16;
     .heap (NOLOAD) : ALIGN(16) {
       _HEAP_START_ = .;
       . = . + HEAP_SIZE;
       _HEAP_END_ = .;
     }

     STACK_SIZE = 8M;
     . = ORIGIN(RAM) + LENGTH(RAM) - STACK_SIZE;
     .stack (NOLOAD) : ALIGN(16)
     {
	       _STACK_END_ = .;
	       . = . + STACK_SIZE;
	       _STACK_START_ = .; 
     } > RAM
}
