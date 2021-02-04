#ifndef __MONITOR_H__
#define __MONITOR_H__

#include "common.h"

enum { NEMU_STOP, NEMU_RUNNING, NEMU_END, NEMU_ABORT };

typedef struct {
  int state;
  vaddr_t halt_pc;
  uint32_t halt_ret;
} NEMUState;

extern NEMUState nemu_state;

#endif
