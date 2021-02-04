#include "cpu/exec.h"

make_EHelper(inv);
make_EHelper(nemu_trap);
//load store
make_EHelper(ld);
make_EHelper(st);
make_EHelper(lh);
make_EHelper(lb);
make_EHelper(lui);
make_EHelper(auipc);
make_EHelper(jal);
make_EHelper(jalr);
make_EHelper(branch);
make_EHelper(imm);
make_EHelper(reg);
make_EHelper(sys);
