#ifndef ISA_H
#define ISA_H

#include <stdint.h>

#include "cpu.h"

// instruction set architecture
// assign an opcode to each instruction
// 16 bit instructions

#define ADD 0x0001      // ADD A, B
#define SUB 0x0002      // SUB A, B
#define MUL 0x0003      // MUL A, B
#define DIV 0x0004      // DIV A, B

#define MOV 0x0005      // MOV A, B
#define LDR 0x0006      // LDR A

#define SHF 0x0007      // SHF A, B
#define ROT 0x0008      // ROT A, B

#define AND 0x0009      // AND A, B
#define OR  0x000A      // OR  A, B
#define XOR 0x000B      // XOR A, B
#define NOT 0x000C      // NOT A

#define CMP 0x000F      // CMP A, B
#define JMP 0x0010      // JMP A
#define JZ  0x0011      // JZ  A
#define JNZ 0x0012      // JNZ A
#define JG  0x0013      // JG  A
#define JL  0x0014      // JL  A
#define JGE 0x0015      // JGE A
#define JLE 0x0016      // JLE A
#define JE  0x0017      // JEQ A
#define JNE 0x0018      // JNE A

// assign an opcode to each register
#define A 0xC00A
#define B 0xC00B
#define MEM 0xC00C  



/* ARITHMETIC */

// ADD A, B into A
extern void _ADD(uint16_t *a, uint16_t *b, Flags *flags);
// SUB A, B into A
extern void _SUB(uint16_t *a, uint16_t *b, Flags *flags);
// MULT A, B into A
extern void _MUL(uint16_t *a, uint16_t *b, Flags *flags);
// DIV A, B into A
extern void _DIV(uint16_t *a, uint16_t *b, Flags *flags);



/* MOVE DATA AND STORE ADDERSSES */

// MOV B into A
extern void _MOV(uint16_t *a, uint16_t *b);
// LDR B address into A
extern void *_LDR(uint16_t offset, CPU *cpu);



/* BITWISE OPERATORS */

// SHF A by B
extern void _SHF(uint16_t *a, uint16_t *b, Flags *flags);
// ROT A by B
extern void _ROT(uint16_t *a, uint16_t *b, Flags *flags);



/* LOGICAL OPERATORS */

// AND A, B into A
extern void _AND(uint16_t *a, uint16_t *b, Flags *flags);
// OR A, B into A
extern void _OR(uint16_t *a, uint16_t *b, Flags *flags);
// XOR A, B into A
extern void _XOR(uint16_t *a, uint16_t *b, Flags *flags);
// NOT A
extern void _NOT(uint16_t *a, Flags *flags);



/* COMPARE AND JUMP */

// CMP A, B
extern void _CMP(uint16_t *a, uint16_t *b, Flags *flags);
// JMP to addr
extern void *_JMP(uint16_t *addr, CPU *cpu);
// JZ to addr if zero flag is set
extern void *_JZ(uint16_t *addr, CPU *cpu);
// JNZ to addr if zero flag is not set
extern void *_JNZ(uint16_t *addr, CPU *cpu);
// JG to addr if greater than flag is set
extern void *_JG(uint16_t *addr, CPU *cpu);
// JL to addr if less than flag is set
extern void *_JL(uint16_t *addr, CPU *cpu);
// JGE to addr if greater than or equal to flag is set
extern void *_JGE(uint16_t *addr, CPU *cpu);
// JLE to addr if less than or equal to flag is set
extern void *_JLE(uint16_t *addr, CPU *cpu);
// JEQ to addr if equal to flag is set
extern void *_JE(uint16_t *addr, CPU *cpu);
// JNE to addr if not equal to flag is set
extern void *_JNE(uint16_t *addr, CPU *cpu);




// END
extern void _END(CPU *cpu);

#endif /* ISA_H__ */