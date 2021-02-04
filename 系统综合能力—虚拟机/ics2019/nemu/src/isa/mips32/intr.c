#include "rtl/rtl.h"
#include <setjmp.h>

void raise_intr(uint32_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * That is, use ``NO'' to index the IDT.
   */
}

bool isa_query_intr(void) {
  return false;
}

jmp_buf intr_buf;

void longjmp_raise_intr(uint32_t NO) {
  longjmp(intr_buf, NO + 1);
}
