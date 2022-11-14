#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "lib/cpu.h"
#include "lib/isa.h"


int main(int argc, char **argv) {
    CPU *cpu = init_cpu();

    // load program memory from file
    load_memory_from_file(cpu->memory, "memory.bin");

    // find magic number in memory to start program and set pc to next instruction
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (cpu->memory->addr[i] == PROGRAM_START) {
            cpu->registers->pc = &cpu->memory->addr[i+1];
            break;
        }
    }

    // set registers to a = 10, b = 20
    cpu->registers->a = 10;
    cpu->registers->b = 10;

    // fetch, decode, execute while pc is not at end of program
    while (*cpu->registers->pc != PROGRAM_END) {
        printf("\n\nEXECUTE PC: 0x%04X\n", *cpu->registers->pc);
        decode_execute(cpu);
    }

    // print cpu state
    print_cpu_state(cpu);

    kill_cpu(cpu);

    return 0;
}