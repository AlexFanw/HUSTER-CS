#include "nemu.h"

static inline paddr_t va2pa(vaddr_t addr, bool write) {
  return addr;
}

uint32_t isa_vaddr_read(vaddr_t addr, int len) {
  return paddr_read(va2pa(addr, false), len);
}

void isa_vaddr_write(vaddr_t addr, uint32_t data, int len) {
  paddr_write(va2pa(addr, true), data, len);
}
