#include "memory.h"
#include "cpu.h"
#include "ppu.h"
#include "psg.h"

byte memory_readb(word address) {
  switch (address >> 13) {
    case 0: return cpu_ram_read(address & 0x07FF);
    case 1: return ppu_io_read(address);
    case 2: return psg_io_read(address);
    case 3: return cpu_ram_read(address & 0x1FFF);
    default: return mmc_read(address);
  }
}

void memory_writeb(word address, byte data) {
  // DMA transfer
  int i;
  if (address == 0x4014) {
    for (i = 0; i < 256; i++) {
      ppu_sprram_write(cpu_ram_read((0x100 * data) + i));
    }
    return;
  }
  switch (address >> 13) {
    case 0: return cpu_ram_write(address & 0x07FF, data);
    case 1: return ppu_io_write(address, data);
    case 2: return psg_io_write(address, data);
    case 3: return cpu_ram_write(address & 0x1FFF, data);
    default: return mmc_write(address, data);
  }
}

word memory_readw(word address) {
  return memory_readb(address) + (memory_readb(address + 1) << 8);
}

void memory_writew(word address, word data) {
  memory_writeb(address, data & 0xFF);
  memory_writeb(address + 1, data >> 8);
}
