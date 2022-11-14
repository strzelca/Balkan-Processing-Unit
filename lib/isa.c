#include <stdlib.h>

#include "isa.h"
#include "cpu.h"

void _ADD(uint16_t *a, uint16_t *b, Flags *flags) {
    uint16_t result = *a + *b;
    if (result == 0) {
        flags->zero = 1;
    } else {
        flags->zero = 0;
    }
    if (result > 0xFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7F) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0xFF) {
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
    if (result > 0xFF) {
        flags->carry = 1;
    } else {
        flags->carry = 0;
    }
    if (result > 0x7F) {
        flags->negative = 1;
    } else {
        flags->negative = 0;
    }
    if (result > 0xFF) {
        flags->overflow = 1;
    } else {
        flags->overflow = 0;
    }
    *a = result;
}

void _END(CPU *cpu) {
    kill_cpu(cpu);
    exit(0);
}