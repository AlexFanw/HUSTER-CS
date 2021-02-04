#include "nemu.h"

// this is not consistent with uint8_t
// but it is ok since we do not access the array directly
const uint32_t isa_default_img [] = {
  0x3c048000,  // lui a0, 0x8000
  0xac800000,  // sw  zero, 0(a0)
  0x8c820000,  // lw  v0,0(a0)
  0xf0000000,  // nemu_trap
};
const long isa_default_img_size = sizeof(isa_default_img);

static void restart() {
  /* Set the initial program counter. */
  cpu.pc = PC_START;

  /* The zero register is always 0. */
  cpu.gpr[0]._32 = 0;
}

void init_isa(void) {
  /* Setup physical memory address space. */
  register_pmem(0x80000000u);

  /* Initialize this virtual computer system. */
  restart();
}
