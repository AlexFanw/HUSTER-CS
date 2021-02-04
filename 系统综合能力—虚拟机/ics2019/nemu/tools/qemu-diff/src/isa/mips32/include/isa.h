#ifndef __MIPS32_H__
#define __MIPS32_H__

#define _str(x) # x
#define str(x) _str(x)

#define ISA_QEMU_BIN "qemu-system-mipsel"
#define ISA_QEMU_ARGS "-machine", "mipssim",\
  "-kernel", str(NEMU_HOME) "/tools/qemu-diff/src/isa/mips32/mips.dummy",

#include "../../../../../../src/isa/mips32/include/isa/diff-test.h"

union isa_gdb_regs {
  struct {
    uint32_t gpr[32];
    uint32_t status, lo, hi, badvaddr, cause, pc;
  };
  struct {
    uint32_t array[77];
  };
};

#endif
