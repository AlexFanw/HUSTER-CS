#include <am.h>

int _mpe_init(void (*entry)()) {
  entry();
  return 1;
}

int _ncpu() {
  return 1;
}

int _cpu() {
  return 0;
}

intptr_t _atomic_xchg(volatile intptr_t *addr, intptr_t newval) {
  intptr_t result;
  asm volatile ("lock xchg %0, %1":
    "+m"(*addr), "=a"(result) : "1"(newval) : "cc");
  return result;
}
