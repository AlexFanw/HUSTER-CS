#ifndef __TRAP_H__
#define __TRAP_H__

#include <am.h>
#include <klib.h>

__attribute__((noinline))
void nemu_assert(int cond) {
  if (!cond) _halt(1);
}

#endif
