#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

#include "cpu.h"
#include "isa.h"

#define DEBUG 1


// initialize memory 0x0000 - 0xFFFF and set all at 0 
void init_memory(Memory *memory) {
    memory->addr = (uint16_t *)malloc(0xFFFF * sizeof(uint16_t));
    memset(memory->addr, 0, 0xFFFF);
}

// initialize registers
void init_registers(Register *registers) {
    registers->a = 0x0;
    registers->b = 0x0;
    registers->sp = NULL;
    registers->pc = NULL;
    registers->mem = NULL;
    registers->flags = (Flags *)malloc(sizeof(Flags));
    memset(registers->flags, 0, sizeof(Flags));
}

// initialize cpu

CPU *init_cpu() {
    CPU *cpu = (CPU*)malloc(sizeof(CPU));
    cpu->registers = (Register*)malloc(sizeof(Register));
    init_registers(cpu->registers);
    cpu->memory = (Memory*)malloc(sizeof(Memory));
    init_memory(cpu->memory);

    cpu->registers->mem = &cpu->memory->addr[MEMORY_START];
    cpu->registers->sp = &cpu->memory->addr[STACK_START];
    return cpu;
}

// free memory
void kill_cpu(CPU *cpu) {
    free(cpu->registers->flags);
    free(cpu->registers);
    free(cpu->memory->addr);
    free(cpu->memory);
    free(cpu);
}

int check_memory_clean(Memory *memory) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory->addr[i] != 0) {
            printf("Memory not clean at address: 0x%04X - Value: 0x%04X\n", i, memory->addr[i]);
            return 1;
        }
    }
    return 0;
}

void write_memory_to_file(Memory *memory, char *filename) {
    // write as binary
    FILE *file = fopen(filename, "wb");
    fwrite(memory->addr, sizeof(uint16_t), MEMORY_SIZE, file);
    fclose(file);
}

void load_memory_from_file(Memory *memory, char *filename) {
    // read as binary
    FILE *file = fopen(filename, "rb");
    fread(memory->addr, sizeof(uint16_t), MEMORY_SIZE, file);
    fclose(file);
}

// print flags status
void print_flags_state(CPU *cpu) {
    printf("FLAGS:\n");
    printf("Z: %d - ", cpu->registers->flags->zero);
    printf("C: %d - ", cpu->registers->flags->carry);
    printf("N: %d - ", cpu->registers->flags->negative);
    printf("O: %d\n", cpu->registers->flags->overflow);
}

// print cpu state
void print_cpu_state(CPU *cpu) {
    printf("CPU STATE:\n");
    printf("A: %d - 0x%X\n", cpu->registers->a, cpu->registers->a);
    printf("B: %d - 0x%X\n", cpu->registers->b, cpu->registers->b);
    printf("SP: %p\n", cpu->registers->sp);
    printf("PC: %p\n", cpu->registers->pc);
    printf("PC VALUE: 0x%04X\n", *cpu->registers->pc);
    printf("MEM: %p\n", cpu->registers->mem);
    if (check_memory_clean(cpu->memory) == 0) {
        printf("Memory clean\n");
    }
    print_flags_state(cpu);
}

// fetch instruction from memory at pc
uint16_t fetch(CPU *cpu) {
    uint16_t instruction = *cpu->registers->pc;
    #ifdef DEBUG
    printf("-- FETCH: 0x%04X\n", instruction);
    print_cpu_state(cpu);
    printf("-- END FETCH\n\n");
    #endif
    cpu->registers->pc++;
    return instruction;
}

// get register shifting program counter to next 2 bytes
// 16 bit register
uint16_t *decode_register(CPU *cpu) {
    uint16_t reg = fetch(cpu);
    switch (reg) {
        case A:
            return &cpu->registers->a;
        case B:
            return &cpu->registers->b;
        default:
            printf("Invalid register: 0x%04X\n", reg);
            return NULL;
    }
}

// decode instruction
void decode_execute(CPU *cpu) {
    uint16_t instruction = fetch(cpu);
    switch (instruction)
    {
    case ADD:
        _ADD(decode_register(cpu), decode_register(cpu), cpu->registers->flags);
        break;
    case SUB:
        _SUB(decode_register(cpu), decode_register(cpu), cpu->registers->flags);
        break;
    default:
        _END(cpu);
        printf("Unknown instruction: 0x%04X\n", instruction);
        break;
    }
}