    .section .text.startup, "ax", %progbits
    .global _start
    .extern main
    .extern __stack_top
    .arm

_start:
    cpsid   if              @ Disable IRQ and FIQ
    ldr     r0, =__stack_top
    mov     sp, r0          @ Initialize stack pointer
    bl      main            @ Jump to C main
1:  b       1b              @ Infinite loop after main returns
