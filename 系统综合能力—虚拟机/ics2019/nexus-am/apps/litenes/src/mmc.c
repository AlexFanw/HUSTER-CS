#include "mmc.h"
#include "ppu.h"
#include <klib.h>

#define MMC_MAX_PAGE_COUNT 1

static byte mmc_chr_pages[MMC_MAX_PAGE_COUNT][0x2000];
static int mmc_chr_pages_number;

byte memory[0x10000];

byte mmc_read(word address) {
  return memory[address];
}

void mmc_write(word address, byte data) {
  switch (mmc_id) {
    case 0x3: ppu_copy(0x0000, &mmc_chr_pages[data & 3][0], 0x2000); break;
  }
  memory[address] = data;
}

void mmc_copy(word address, byte *source, int length) {
  memcpy(&memory[address], source, length);
}

void mmc_append_chr_rom_page(byte *source) {
  assert(mmc_chr_pages_number < MMC_MAX_PAGE_COUNT);
  memcpy(&mmc_chr_pages[mmc_chr_pages_number++][0], source, 0x2000);
}
