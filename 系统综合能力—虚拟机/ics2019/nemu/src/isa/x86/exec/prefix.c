#include "cpu/exec.h"

void isa_exec(vaddr_t *pc);

make_EHelper(operand_size) {
  decinfo.isa.is_operand_size_16 = true;
  isa_exec(pc);
  decinfo.isa.is_operand_size_16 = false;
}
