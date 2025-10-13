## Advanced linker script

To understand available layout first we need to undewrstand which regions are taken:
```
STM32MP> bdinfo
lmb_dump_all:
 memory.cnt = 0x1 / max = 0x2
 memory[0]      [0xc0000000-0xdfffffff], 0x20000000 bytes flags: 0
 reserved.cnt = 0x2 / max = 0x10
 reserved[0]    [0xd9f20000-0xdfffffff], 0x060e0000 bytes flags: 0
 reserved[1]    [0xdd000000-0xdfffffff], 0x03000000 bytes flags: 4
```

We can read that taken memory addresses spawn from 0xd9f20000 to 0xdfffffff and 0xdd000000 to 0xdfffffff.

So we can assume that our memory can start from 0xc0000000 and end up on 0xd9f20000 so we do not overlap 
with already taken memory.

The layout of the linker script is as following:
```
   |--- 0xC0000000: Ram start 
   |
   |
   |--- 0xC0300000: App memory start 
   |
   |
   |---
```

