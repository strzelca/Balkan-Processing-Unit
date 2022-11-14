# Balkan Processing Unit

The **Balkan Processing Unit** _(BPU)_ is a microprocessor powered by war crimes and ethnic cleansing.

**BPU** Architecture:
* Register **A**
* Register **B**
* Register **SP** _(Stack Pointer)_
* Register **PC** _(Program Counter)_
* Register **MEM** _(Memory Pointer)_
* Flags _(Zero, Carry, Negative, Overflow)_

The memory space is **0x0000 - 0xFFFF**
 
Stack starts at **0xFFFE** and ends at **0xFF00**

When microprocessor encounters a memory location with value **0xBEEF**, it sets PC Register at the next address. At this point the program execution starts and it goes through the _fetch-decode-execute_ cycle unitl it finds the value **0xDEAD**, the stop magic number.

## Instruction Set
---
Do A + B and store result into A
```assembly
ADD A, B
``` 

Do A - B and store result into A
```assembly
SUB A, B
``` 