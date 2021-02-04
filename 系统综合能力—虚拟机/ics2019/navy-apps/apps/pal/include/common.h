#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdint.h>

typedef uint8_t bool;

#define true         1
#define false        0

#define Log(args...) do { fprintf(stderr, args); fprintf(stderr, "\n"); } while (0)

void SDL_WaitUntil(uint32_t tick);

#endif
