#ifndef ISA_H
#define ISA_H

#include <stdint.h>

#include "cpu.h"

// assign an opcode to each instruction
// 16 bit instructions
#define ADD 0x0001
#define SUB 0x0002
#define MUL 0x0003
#define DIV 0x0004
#define MOV 0x0005
#define LDR 0x0006
#define SHF 0x0007

// assign an opcode to each register
#define A 0xC00A
#define B 0xC00B
#define MEM 0xC00C  


// instruction set architecture
// 8 bit instructions

// ADD A, B into A
extern void _ADD(uint16_t *a, uint16_t *b, Flags *flags);
// SUB A, B into A
extern void _SUB(uint16_t *a, uint16_t *b, Flags *flags);
// MULT A, B into A
extern void _MUL(uint16_t *a, uint16_t *b, Flags *flags);
// DIV A, B into A
extern void _DIV(uint16_t *a, uint16_t *b, Flags *flags);
// MOV B into A
extern void _MOV(uint16_t *a, uint16_t *b);
// LDR B address into A
extern void *_LDR(uint16_t offset, CPU *cpu);
// SHF A by B
extern void _SHF(uint16_t *a, uint16_t *b, Flags *flags);
// END
extern void _END(CPU *cpu);

#endif /* ISA_H__ */