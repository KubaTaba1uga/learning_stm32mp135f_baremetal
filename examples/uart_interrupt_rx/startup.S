.syntax unified
.cpu cortex-a7
	
.global _Reset
.extern main
.extern _STACK_START_
.extern _VECTORS_TABLE_START_
.arm

.equ MODE_IRQ, 0x12 @ Interrupt mode
.equ MODE_SYS, 0x1F @ System mode

_Reset:
    cpsid   if                         @ Disable IRQ and FIQ

    mrc     p15, 0, r0, c1, c0, 0      @ Read System Control register (SCTLR)
    bic     r0, r0, #(0x1 << 13)       @ Clear V bit 13 to disable High Vector Table Base Address
    mcr     p15, 0, r0, c1, c0, 0      @ Write System Control register (SCTLR)
	
    ldr    R0, =_VECTORS_TABLE_START_  @ Load addres of vector table to r0
    mcr    p15, 0, R0, c12, c0, 0      @ Load r0 to VBAR

    cpsid   if, #MODE_IRQ              @ SET Cpu into IRQ mode
    ldr r0, =_IRQ_STACK_START_         @ Load start of IRQ stack to r0
    mov sp, r0                         @ Initialize IRQ stack pointer

    cpsid   if, #MODE_SYS              @ SET Cpu into System mode
    ldr     r0, =_STACK_START_         @ Load value to register 0
    mov     sp, r0                     @ Initialize stack pointer	
    CPSIE  i			       @ enable irq interrupts
    bl      main                       @ Jump to C main
    b       .                          @ Infinite loop after main returns
