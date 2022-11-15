#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "lib/cpu.h"
#include "lib/isa.h"


int main(int argc, char **argv) {
    CPU *cpu = init_cpu();

    // load program memory from file
    load_memory_from_file(cpu->memory, "memory.bin");

    find_magic_number(cpu);

    // fetch, decode, execute while pc is not at end of program
    while (*cpu->registers->pc != PROGRAM_END) {
        printf("EXECUTE PC: 0x%04X\n", *cpu->registers->pc);
        decode_execute(cpu);
    }

    // print cpu state
    print_cpu_state(cpu);

    kill_cpu(cpu);

    return 0;
}