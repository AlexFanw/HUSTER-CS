#include <common.h>
#include <mmc.h>
#include <ppu.h>

#define MMC_MAX_PAGE_COUNT 1

byte mmc_id;

byte mmc_chr_pages[MMC_MAX_PAGE_COUNT][0x2000];
int mmc_chr_pages_number;

byte memory[0x10000];

inline byte mmc_read(word address)
{
    return memory[address];
}

inline void mmc_write(word address, byte data)
{
    memory[address] = data;
}

inline void mmc_copy(word address, byte *source, int length)
{
    memcpy(&memory[address], source, length);
}

inline void mmc_append_chr_rom_page(byte *source)
{
    memcpy(&mmc_chr_pages[mmc_chr_pages_number++][0], source, 0x2000);
}
