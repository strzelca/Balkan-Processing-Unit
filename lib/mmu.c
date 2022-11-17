#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <stdint.h>

#include "mmu.h"
#include "cpu.h"

/* ROM */

Bank *init_bank(uint8_t bank_number) {
    Bank *bank = (Bank *)malloc(sizeof(Bank));
    bank->bank_number = bank_number;
    bank->bank_memory = (Memory *)malloc(sizeof(Memory));
    init_memory(bank->bank_memory);
    return bank;
}

void kill_bank(Bank *bank) {
    free(bank->bank_memory->addr);
    free(bank->bank_memory);
    free(bank);
}


/* VRAM */

VRAM *init_vram() {
    VRAM *vram = (VRAM *)malloc(sizeof(VRAM));
    vram->vram = (uint8_t *)malloc(VRAM_SIZE);
    memset(vram->vram, 0, VRAM_SIZE);
    return vram;
}

void kill_vram(VRAM *vram) {
    free(vram->vram);
    free(vram);
}


/* IO */

IO *init_io() {
    IO *io = (IO *)malloc(sizeof(IO));
    io->io = (uint8_t *)malloc(IO_SIZE);
    memset(io->io, 0, IO_SIZE);
    return io;
}

void kill_io(IO *io) {
    free(io->io);
    free(io);
}

// map banks, vram and io to virtual address table
void map_mmu(MMU *mmu) {
    for (int i = 0; i < ROM_VIRTUAL_ADDRESS_END; i++) {
        uint8_t bank = (i / MEMORY_SIZE);
        uint8_t offset = i - (bank * MEMORY_SIZE);
        mmu->virtual_address_table[i] = (uintptr_t)&mmu->bank[bank]->bank_memory->addr[offset];
        printf("Virtual address table at address: 0x%05X - Real Bank [%d] Address: 0x%04X\n", i, bank, offset);
    }
    for (int i = 0; i < VRAM_SIZE; i++) {
        mmu->virtual_address_table[VRAM_VIRTUAL_ADDRESS_START+i] = (uintptr_t)&mmu->vram->vram[i];
    }
    for (int i = 0; i < IO_SIZE; i++) {
        mmu->virtual_address_table[IO_VIRTUAL_ADDRESS_START+i] = (uintptr_t)&mmu->io->io[i];
    }
}

/* MMU */

MMU *init_mmu() {
    MMU *mmu = (MMU *)malloc(sizeof(MMU));
    for (int i = 0; i < 8; i++) {
        mmu->bank[i] = init_bank(i);
    }
    mmu->vram = init_vram();
    mmu->io = init_io();
    mmu->virtual_address_table = (uintptr_t *)malloc(((MEMORY_SIZE*8)+VRAM_SIZE+IO_SIZE) * sizeof(intptr_t));
    map_mmu(mmu);
    return mmu;
}

void kill_mmu(MMU *mmu) {
    for (int i = 0; i < 8; i++) {
        kill_bank(mmu->bank[i]);
    }
    kill_vram(mmu->vram);
    kill_io(mmu->io);
    free(mmu->virtual_address_table);
    free(mmu);
}


// translate each virtual address for each bank to real address of them
uintptr_t translate_address(MMU *mmu, uintptr_t address) {
    // calculate exact position of real address in virtual address table
    uintptr_t position = (address & 0x1FFF) + ((address & 0x6000) >> 3);
    return (intptr_t) &mmu->virtual_address_table[position];
}

