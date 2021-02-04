#include <am.h>

int _mpe_init(void (*entry)()) {
  return 1;
}

int _ncpu() {
  return 1;
}

int _cpu() {
  return 0;
}

intptr_t _atomic_xchg(volatile intptr_t *addr, intptr_t newval) {
  return 0;
}
