#ifndef FCE_H
#define FCE_H

#include <common.h>

#define FPS 60
#define W   256
#define H   240

extern byte canvas[H][W];

void fce_update_screen();

extern char rom_mario_nes[];
extern char rom_kungfu_nes[];

#endif
