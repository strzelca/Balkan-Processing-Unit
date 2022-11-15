// THIS IS THE HEADER FILE FOR THE cpu.c FILE
#ifndef CPU_H__
#define CPU_H__

#define MEMORY_SIZE 0xFFFF

#define MEMORY_START 0x0000
#define MEMORY_END 0xFFFF

#define STACK_START 0xFFFE
#define STACK_END 0xFF00


// magic number to start program

#define PROGRAM_START 0xBEEF
#define PROGRAM_END 0xDEAD

#include <stdint.h>

// crete a struct for cpu flags zero, carry, negative, overflow as 1 bit each array
typedef struct _flags {
    uint8_t zero:1;
    uint8_t carry:1;
    uint8_t negative:1;
    uint8_t overflow:1;
} Flags;

// registers a,b,sp,pc,mem,flags
// 8 bit registers
// are pointers to 8 bit values

typedef struct _register {
    uint16_t a;
    uint16_t b;
    uint16_t *sp;
    uint16_t *pc;
    uint16_t *mem;
    Flags *flags;
} Register;

// struct for memory with addresses from 0x0000 to 0xFFFF (65535 bytes)
typedef struct _memory {
    uint16_t *addr;
} Memory;

// CPU struct with initialized pointer to registers
typedef struct _cpu {
    Register *registers;
    Memory *memory;
} CPU;


extern CPU *init_cpu();
extern void kill_cpu(CPU *cpu);
extern void print_cpu_state(CPU *cpu);
extern void print_flags_state(CPU *cpu);
extern int check_memory_clean(Memory *memory);
extern void write_memory_to_file(Memory *memory, char *filename);
extern void load_memory_from_file(Memory *memory, char *filename);
extern void find_magic_number(CPU *cpu);


// execute instruction
extern void decode_execute(CPU *cpu);
#endif /* CPU_H__ */