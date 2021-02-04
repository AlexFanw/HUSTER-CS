#ifndef MEM_H
#define MEM_H

#include "common.h"
#include "mmc.h"

// Single byte
byte memory_readb(word address);
void memory_writeb(word address, byte data);

// Two bytes (word), LSB first
word memory_readw(word address);
void memory_writew(word address, word data);

#endif
