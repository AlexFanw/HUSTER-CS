#include "nemu.h"

// this is not consistent with uint8_t
// but it is ok since we do not access the array directly
const uint32_t isa_default_img [] = {
  0x800002b7,  // lui t0,0x80000
  0x0002a023,  // sw  zero,0(t0)
  0x0002a503,  // lw  a0,0(t0)
  0x0000006b,  // nemu_trap
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
