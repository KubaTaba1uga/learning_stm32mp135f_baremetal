ENTRY(_start)

 SECTIONS
 {
   . = 0xC0300000;

   .text : ALIGN(4) { *(.text*) }
   .rodata : ALIGN(4) { *(.rodata*) }
   .data   : ALIGN(4) { *(.data*) }
   .bss (NOLOAD) : ALIGN(4) { *(.bss*) *(COMMON) }

   /* -------- Stack -------- */
   /* Minimal fixed-size stack near the image. Tweak as needed. */
   STACK_SIZE = 64K;
   . = ALIGN(16);
   __stack_bottom = .;
   .stack (NOLOAD) : ALIGN(16)
   {
     . = . + STACK_SIZE;
   }
   __stack_top = .;
}
