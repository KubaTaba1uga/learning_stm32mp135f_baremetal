/*
  Set the program’s entry point symbol to _start.
*/
ENTRY(_start) 

/*
  Define memory layout.
*/
 SECTIONS
 {
   /*
     Define starting block for next section.
   */
   . = 0xC0300000;

   /*
     Declare sections required by C.
     Sections need to be aligned to 32 bits because STM32MP135f
     word is 32 bits.

     text section store the code

     rodata store initialized read only data

     data store initialized editable data
   */
   .text : ALIGN(4) { *(.text*) }
   .rodata : ALIGN(4) { *(.rodata*) }
   .data   : ALIGN(4) { *(.data*) }
   
   /*
     bss store unitintialized editable data

     NOLOAD tells linker that this section does not need to be loaded to memory.
     However memory for it still is allocated. If we ommit NOLOAD the binnary will
     just get bigger.

     We added -fno-common flag so we can skip COMMON directive.
   */
   .bss (NOLOAD) : ALIGN(4) { *(.bss*) }

   /* -------- Stack -------- */
   
   STACK_SIZE = 64K;
   . = ALIGN(16);
   /*
     Creates a symbol at the lowest address of the stack area.
     __stack_bottom can be used to detect stack overflow.
   */
   __stack_bottom = .;
   .stack (NOLOAD) : ALIGN(16)
   {
     . = . + STACK_SIZE;
   }
   /*
     Creates a symbol at the highest address of the stack area.
     __stack_top is a start of the stack.
   */   
   __stack_top = .;
}
