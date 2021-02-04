#ifndef __RISCV32_H__
#define __RISCV32_H__

#define ISA_QEMU_BIN "qemu-system-riscv32"
#define ISA_QEMU_ARGS 

#include "../../../../../../src/isa/riscv32/include/isa/diff-test.h"

union isa_gdb_regs {
  struct {
    uint32_t gpr[32];
    uint32_t pc;
  };
  struct {
    uint32_t array[77];
  };
};

#endif
