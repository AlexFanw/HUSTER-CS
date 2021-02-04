#include "rtl/rtl.h"

void raise_intr(uint32_t NO, vaddr_t epc) {
  cpu.sepc=epc;
  cpu.scause=NO;
  rtl_j(cpu.stvec);
  //异常返回
}

bool isa_query_intr(void) {
  return false;
}
