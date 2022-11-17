#ifndef MMU_H__
#define MMU_H__

#include <stdint.h>

#include "cpu.h"

/* 
    REAL SPACE
    0x0000 - 0xFFFF Each ROM
    0x0000 - 0x5A00 VRAM
    0x0000 - 0x00FF IO

    VIRTUAL SPACE
    0x00000 - 0x7FFF8 ROM
    0x7FFF9 - 0x858F8 VRAM
    0x858F9 - 0x85AF7 IO

*/

#define IO_SIZE 0x00FF
#define IO_START 0x0000
#define IO_END 0x00FF

#define VRAM_SIZE 0x5A00
#define VRAM_START 0x0000
#define VRAM_END 0x5A00


#define VIRTUAL_ADDRESS_TABLE_SIZE ((MEMORY_SIZE*8)+VRAM_SIZE+IO_SIZE)

#define ROM_VIRTUAL_ADDRESS_START 0x00000
#define ROM_VIRTUAL_ADDRESS_END 0x7FFF8

#define VRAM_VIRTUAL_ADDRESS_START 0x7FFF9
#define VRAM_VIRTUAL_ADDRESS_END 0x858F8

#define IO_VIRTUAL_ADDRESS_START 0x858F9
#define IO_VIRTUAL_ADDRESS_END 0x85AF7




// ROM memory bank
// 0x0000 - 0xFFFF address space
// 2 bytes data width per address
typedef struct _bank {
    uint8_t bank_number;
    struct _memory *bank_memory;
} Bank;

// VRAM memory bank
// 8 bit depth 160x144 pixels
// 0x0000 - 0x5A00 address space
typedef struct _vram {
    uint8_t *vram;
} VRAM;

// IO memory bank
// 0x0000 - 0x00FF address space
typedef struct _io {
    uint8_t *io;
} IO;


// Memory Management Unit
typedef struct _mmu {
    Bank *bank[8];
    VRAM *vram;
    IO *io;
    uintptr_t *virtual_address_table;
} MMU;

// initialize mmu
extern MMU *init_mmu();
// free mmu
extern void kill_mmu(MMU *mmu);

// translate virtual address to real address
extern uintptr_t translate_address(MMU *mmu, uintptr_t address);
extern uint16_t real_address_value(MMU *mmu, uintptr_t address);

#endif