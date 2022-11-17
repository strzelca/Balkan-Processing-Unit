#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

#include "cpu.h"
#include "isa.h"

// #define DEBUG


// initialize memory 0x0000 - MEMORY_SIZE and set all at 0 
void init_memory(Memory *memory) {
    memory->addr = (uint16_t *)malloc(MEMORY_SIZE * sizeof(uint16_t));
    memset(memory->addr, 0, MEMORY_SIZE);
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
    cpu->mmu = init_mmu();

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
    kill_mmu(cpu->mmu);
    free(cpu);
}

int check_memory_clean(Memory *memory) {
    uint8_t c = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory->addr[i] != 0) {
            printf("Memory not clean at address: 0x%04X - Value: 0x%04X\n", i, memory->addr[i]);
            c++;
        }
    }
    return c;
}

int check_memory(Memory *memory) {
    // scan memory and print percentage progress
    uint8_t c = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory->addr[i] != 0) {
            printf("Memory not clean at address: 0x%04X - Value: 0x%04X\n", i, memory->addr[i]);
            c++;
        }
        if (i % 1000 == 0) {
            printf("Memory scan progress: %d%%\r", (i * 100) / MEMORY_SIZE + 1);
            fflush(stdout);
            usleep(5000);
        }
    }
    printf("\n");
    return c;
}

int check_mapped_integrity(MMU *mmu){
    uint8_t c = 0;
    for (int i = 0; i < VIRTUAL_ADDRESS_TABLE_SIZE; i++) {
        if (i >= 0x0000 && i < ROM_VIRTUAL_ADDRESS_END) {
            uint8_t bank = (i / MEMORY_SIZE);
            uint8_t offset = i - (bank * MEMORY_SIZE);
            if (mmu->bank[bank]->bank_memory->addr[offset] != 0) {
                printf("Virtual address table not clean at address: 0x%05X - Value: 0x%04X\n", i, mmu->bank[bank]->bank_memory->addr[offset]);
                c++;
            }
        } else if (i >= VRAM_VIRTUAL_ADDRESS_START && i < VRAM_VIRTUAL_ADDRESS_END) {
            uint8_t offset = i - VRAM_VIRTUAL_ADDRESS_START;
            if (mmu->vram->vram[offset] != 0) {
                printf("Virtual address table not clean at address: 0x%05X - Value: 0x%04X\n", i, mmu->vram->vram[offset]);
                c++;
            }
        } else if (i >= IO_VIRTUAL_ADDRESS_START && i < IO_VIRTUAL_ADDRESS_END) {
            uint8_t offset = i - IO_VIRTUAL_ADDRESS_START;
            if (mmu->io->io[offset] != 0) {
                printf("Virtual address table not clean at address: 0x%05X - Value: 0x%04X\n", i, mmu->io->io[offset]);
                c++;
            }
        }
        if (i % 1000 == 0) {
            printf("Mapped memory scan progress: %d%%\r", (i * 100) / VIRTUAL_ADDRESS_TABLE_SIZE + 1);
            fflush(stdout);
            usleep(1000);
        }
    }
    printf("\n");
    return c;
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

// find magic number in memory and set pc to that address
void find_magic_number(CPU *cpu) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (cpu->memory->addr[i] == PROGRAM_START) {
            cpu->registers->pc = &cpu->memory->addr[i+1];
            return;
        }
    }
    printf("Magic number not found in memory!\n");
    exit(1);
}

// get virtual address from physical address
uint16_t get_virtual_address(Memory *memory, uint16_t *physical_address) {
    uint16_t *physical_address_start = &memory->addr[MEMORY_START];
    
    int offset = (intptr_t) physical_address - (intptr_t) physical_address_start;
    return offset >> 1;

}

// print flags status
void print_flags_state(CPU *cpu) {
    printf("");
    printf("FLAGS:\nZ: %d - C: %d - N: %d - O: %d\n",
            cpu->registers->flags->zero,
            cpu->registers->flags->carry,
            cpu->registers->flags->negative,
            cpu->registers->flags->overflow
    );
}

// print cpu state
void print_cpu_state(CPU *cpu) {
    printf("CPU STATE:\n");
    printf("A: %d - 0x%X\n", (int16_t) cpu->registers->a, cpu->registers->a);
    printf("B: %d - 0x%X\n", (int16_t) cpu->registers->b, cpu->registers->b);
    printf("SP: 0x%04X\n", get_virtual_address(cpu->memory, cpu->registers->sp));
    printf("PC: 0x%04X -> 0x%04X\n", get_virtual_address(cpu->memory, cpu->registers->pc), *cpu->registers->pc);
    printf("MEM: 0x%04X -> 0x%04X\n", get_virtual_address(cpu->memory, cpu->registers->mem), *cpu->registers->mem);
    if (check_memory(cpu->memory) == 0) { printf("Memory clean\n"); }
    if (check_mapped_integrity(cpu->mmu) == 0) { printf("Mapped Memory Clean\n"); }
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
uint16_t *decode_data(CPU *cpu) {
    uint16_t reg = fetch(cpu);
    switch (reg) {
        case A:
            return &cpu->registers->a;
        case B:
            return &cpu->registers->b;
        case MEM:
            return cpu->registers->mem;
        default:
            return &reg;
    }
}

// decode instruction
void decode_execute(CPU *cpu) {
    uint16_t instruction = fetch(cpu);
    switch (instruction)
    {
    case ADD:
        _ADD(decode_data(cpu), decode_data(cpu), cpu->registers->flags);
        break;
    case SUB:
        _SUB(decode_data(cpu), decode_data(cpu), cpu->registers->flags);
        break;
    case MUL:
        _MUL(decode_data(cpu), decode_data(cpu), cpu->registers->flags);
        break;
    case DIV:
        _DIV(decode_data(cpu), decode_data(cpu), cpu->registers->flags);
        break;
    case MOV:
        _MOV(decode_data(cpu), decode_data(cpu));
        break;
    case LDR:
         cpu->registers->mem = _LDR(*decode_data(cpu), cpu);
        break;
    case SHF:
        _SHF(decode_data(cpu), decode_data(cpu), cpu->registers->flags);
        break;
    case ROT:
        _ROT(decode_data(cpu), decode_data(cpu), cpu->registers->flags);
        break;
    case AND:
        _AND(decode_data(cpu), decode_data(cpu), cpu->registers->flags);
        break;
    case OR:
        _OR(decode_data(cpu), decode_data(cpu), cpu->registers->flags);
        break;
    case XOR:
        _XOR(decode_data(cpu), decode_data(cpu), cpu->registers->flags);
        break;
    case NOT:
        _NOT(decode_data(cpu), cpu->registers->flags);
        break;
    case CMP:
        _CMP(decode_data(cpu), decode_data(cpu), cpu->registers->flags);
        break;
    case JMP:
        cpu->registers->pc = _JMP(decode_data(cpu), cpu);
        break;
    case JZ:
        cpu->registers->pc = _JZ(decode_data(cpu), cpu);
        break;
    case JNZ:
        cpu->registers->pc = _JNZ(decode_data(cpu), cpu);
        break;
    case JG:
        cpu->registers->pc = _JG(decode_data(cpu), cpu);
        break;
    case JL:
        cpu->registers->pc = _JL(decode_data(cpu), cpu);
        break;
    case JGE:
        cpu->registers->pc = _JGE(decode_data(cpu), cpu);
        break;
    case JLE:
        cpu->registers->pc = _JLE(decode_data(cpu), cpu);
        break;
    case JE:
        cpu->registers->pc = _JE(decode_data(cpu), cpu);
        break;
    case JNE:
        cpu->registers->pc = _JNE(decode_data(cpu), cpu);
        break;
    default:
        printf("Unknown instruction: 0x%04X\n", instruction);
        break;
    }
}