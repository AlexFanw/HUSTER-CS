#ifndef PPU_H
#define PPU_H

#include "common.h"

typedef struct {
  byte PPUCTRL;   // $2000 write only
  byte PPUMASK;   // $2001 write only
  byte PPUSTATUS; // $2002 read only
  byte OAMADDR;   // $2003 write only
  byte OAMDATA;   // $2004
  word PPUSCROLL;
  byte PPUSCROLL_X, PPUSCROLL_Y; // $2005 write only x2
  word PPUADDR;   // $2006 write only x2
  word PPUDATA;   // $2007

  bool scroll_received_x;
  bool addr_received_high_byte;
  bool ready;

  int mirroring, mirroring_xor;

  int x, scanline;
} PPU_STATE;

void ppu_init();

byte ppu_ram_read(word address);
void ppu_ram_write(word address, byte data);
byte ppu_io_read(word address);
void ppu_io_write(word address, byte data);

bool ppu_generates_nmi();

void ppu_set_mirroring(byte mirroring);

void ppu_cycle();
void ppu_copy(word address, byte *source, int length);
void ppu_sprram_write(byte data);

#endif
