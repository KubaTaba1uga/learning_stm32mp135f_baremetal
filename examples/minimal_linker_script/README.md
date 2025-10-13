## Linker script

Goal of this example is to estabilish minimal linker script and startup assembly
wich allow to execute bare metal code from uboot. 

To run C code first thing we need is configured stack. Stack configuration is composed of two things, linker script part and assembly part. Linker script declare chunk of memory wich will be used by us for the stack, where assembly set up `sp` register to the memory segment set by linker script.



