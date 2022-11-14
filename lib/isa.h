#ifndef ISA_H
#define ISA_H

#include <stdint.h>

#include "cpu.h"

// assign an opcode to each instruction
// 8 bit instructions
#define ADD 0x0001
#define SUB 0x0002

// assign an opcode to each register
#define A 0xC00A
#define B 0xC00B


// instruction set architecture
// 8 bit instructions

// ADD A, B into A
extern void _ADD(uint16_t *a, uint16_t *b, Flags *flags);
// SUB A, B into A
extern void _SUB(uint16_t *a, uint16_t *b, Flags *flags);
// END
extern void _END(CPU *cpu);

#endif /* ISA_H__ */