#include <stdlib.h>
#include <stdio.h>

#include "isa.h"
#include "cpu.h"


// Values are 2 bytes long


/* ARITHMETIC OPERATORS */

void _ADD(uint16_t *a, uint16_t *b, Flags *flags) {
    uint16_t result = *a + *b;
    if (result == 0) {
        flags->zero = 1;
    } else {
        flags->zero = 0;
    }
    if (result > 0xFFFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7FFF) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0x7FFF) {
        flags->overflow = 1;
    } else {
        flags->overflow = 0;
    }
    *a = result;
}

void _SUB(uint16_t *a, uint16_t *b, Flags *flags) {
    uint16_t result = *a - *b;
    if (result == 0) {
        flags->zero = 1;
    } else {
        flags->zero = 0;
    }
    if (result > 0xFFFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7FFF) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0x7FFF) {
        flags->overflow = 1;
    } else {
        flags->overflow = 0;
    }
    *a = result;
}

void _MUL(uint16_t *a, uint16_t *b, Flags *flags) {
    uint16_t result = *a * *b;
    if (result == 0) {
        flags->zero = 1;
    } else {
        flags->zero = 0;
    }
    if (result > 0xFFFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7FFF) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0xFFFF) {
        flags->overflow = 1;
    } else {
        flags->overflow = 0;
    }
    *a = result;
}

void _DIV(uint16_t *a, uint16_t *b, Flags *flags) {
    uint16_t result = *a / *b;
    if (result == 0) {
        flags->zero = 1;
    } else {
        flags->zero = 0;
    }
    if (result > 0xFFFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7FFF) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0xFFFF) {
        flags->overflow = 1;
    } else {
        flags->overflow = 0;
    }
    *a = result;
}



/* MOVE DATA AND STORE ADDERSSES */

void _MOV(uint16_t *a, uint16_t *b) {
    *a = *b;
}

void *_LDR(uint16_t offset, CPU *cpu) {
    // check if offset is in bounds
    if (offset > MEMORY_SIZE) {
        printf("Error: offset out of bounds\n");
        exit(1);
    } else {
        return &cpu->memory->addr[offset];
    }
}



/* BITWISE OPERATORS */

void _SHF(uint16_t *a, uint16_t *b, Flags *flags) {
    uint16_t result = *a << *b;
    if (result == 0) {
        flags->zero = 1;
    } else {
        flags->zero = 0;
    }
    if (result > 0xFFFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7FFF) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0xFFFF) {
        flags->overflow = 1;
    } else {
        flags->overflow = 0;
    }
    *a = result;
}

void _ROT(uint16_t *a, uint16_t *b, Flags *flags) {
    uint16_t result = *a >> *b;
    if (result == 0) {
        flags->zero = 1;
    } else {
        flags->zero = 0;
    }
    if (result > 0xFFFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7FFF) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0xFFFF) {
        flags->overflow = 1;
    } else {
        flags->overflow = 0;
    }
    *a = result;
}



/* LOGICAL OPERATORS */

void _AND(uint16_t *a, uint16_t *b, Flags *flags) {
    uint16_t result = *a & *b;
    if (result == 0) {
        flags->zero = 1;
    } else {
        flags->zero = 0;
    }
    if (result > 0xFFFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7FFF) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0xFFFF) {
        flags->overflow = 1;
    } else {
        flags->overflow = 0;
    }
    *a = result;
}

void _OR(uint16_t *a, uint16_t *b, Flags *flags) {
    uint16_t result = *a | *b;
    if (result == 0) {
        flags->zero = 1;
    } else {
        flags->zero = 0;
    }
    if (result > 0xFFFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7FFF) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0xFFFF) {
        flags->overflow = 1;
    } else {
        flags->overflow = 0;
    }
    *a = result;
}

void _XOR(uint16_t *a, uint16_t *b, Flags *flags) {
    uint16_t result = *a ^ *b;
    if (result == 0) {
        flags->zero = 1;
    } else {
        flags->zero = 0;
    }
    if (result > 0xFFFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7FFF) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0xFFFF) {
        flags->overflow = 1;
    } else {
        flags->overflow = 0;
    }
    *a = result;
}

void _NOT(uint16_t *a, Flags *flags) {
    uint16_t result = ~*a;
    if (result == 0) {
        flags->zero = 1;
    } else {
        flags->zero = 0;
    }
    if (result > 0xFFFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7FFF) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0xFFFF) {
        flags->overflow = 1;
    } else {
        flags->overflow = 0;
    }
    *a = result;
}


/* COMPARE AND JUMP */

void _CMP(uint16_t *a, uint16_t *b, Flags *flags) {
    uint16_t result = *a - *b;
    if (result == 0) {
        flags->zero = 1;
    } else {
        flags->zero = 0;
    }
    if (result > 0xFFFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7FFF) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0xFFFF) {
        flags->overflow = 1;
    } else {
        flags->overflow = 0;
    }
}

void *_JMP(uint16_t *addr, CPU *cpu) {
    return &cpu->memory->addr[*addr];
}

void *_JZ(uint16_t *addr, CPU *cpu) {
    if (cpu->registers->flags->zero == 1) {
        return &cpu->memory->addr[*addr];
    } else {
        return &cpu->registers->pc;
    }
}

void *_JNZ(uint16_t *addr, CPU *cpu) {
    if (cpu->registers->flags->zero == 0) {
        return &cpu->memory->addr[*addr];
    } else {
        return cpu->registers->pc;
    }
}

void *_JG(uint16_t *addr, CPU *cpu) {
    if (cpu->registers->flags->zero == 0 && cpu->registers->flags->negative == 0) {
        return &cpu->memory->addr[*addr];
    } else {
        return &cpu->registers->pc;
    }
}

void *_JL(uint16_t *addr, CPU *cpu) {
    if (cpu->registers->flags->negative == 1) {
        return &cpu->memory->addr[*addr];
    } else {
        return &cpu->registers->pc;
    }
}

void *_JE(uint16_t *addr, CPU *cpu) {
    if (cpu->registers->flags->zero == 1) {
        return &cpu->memory->addr[*addr];
    } else {
        return &cpu->registers->pc;
    }
}

void *_JNE(uint16_t *addr, CPU *cpu) {
    if (cpu->registers->flags->zero == 0) {
        return &cpu->memory->addr[*addr];
    } else {
        return &cpu->registers->pc;
    }
}

void *_JGE(uint16_t *addr, CPU *cpu) {
    if (cpu->registers->flags->negative == 0) {
        return &cpu->memory->addr[*addr];
    } else {
        return &cpu->registers->pc;
    }
}

void *_JLE(uint16_t *addr, CPU *cpu) {
    if (cpu->registers->flags->zero == 1 || cpu->registers->flags->negative == 1) {
        return &cpu->memory->addr[*addr];
    } else {
        return &cpu->registers->pc;
    }
}



void _END(CPU *cpu) {
    kill_cpu(cpu);
    exit(0);
}