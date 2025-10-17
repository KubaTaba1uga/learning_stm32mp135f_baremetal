.syntax unified
.cpu cortex-a7
	
.global _Reset
.extern main
.extern _STACK_START_
.arm

_Reset:
    cpsid   if                   @ Disable IRQ and FIQ
    ldr     r0, =_STACK_START_   @ Load value to register 0
    mov     sp, r0               @ Initialize stack pointer
    bl      main                 @ Jump to C main
    b       .                    @ Infinite loop after main returns
