#ifndef PSG_H
#define PSG_H

#include "common.h"

byte psg_io_read(word address);
void psg_io_write(word address, byte data);
void psg_init();
void psg_detect_key();

#endif
