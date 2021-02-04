#include "common.h"

byte mmc_id;

byte mmc_read(word address);
void mmc_write(word address, byte data);
void mmc_copy(word address, byte *source, int length);
void mmc_append_chr_rom_page(byte *source);