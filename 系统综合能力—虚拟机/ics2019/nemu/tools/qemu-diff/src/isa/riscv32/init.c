#include "common.h"

bool gdb_memcpy_to_qemu(uint32_t, void *, int);
bool gdb_getregs(union isa_gdb_regs *);
bool gdb_setregs(union isa_gdb_regs *);
void difftest_exec(uint64_t n);

static uint32_t initcode[] = {
  0x800006b7,  // lui a3,0x8000
  0x03c68693,  // addi a3,a3,0x3c # 800003c
  0x30569073,  // csrw mtvec,a3

  0xfff00513,  // li a0, -1
  0x01f00593,  // li a1, 31
  0x3b051073,  // csrw pmpaddr0, a0
  0x3a059073,  // csrw pmpcfg0, a1

  0x000c1637,  // lui a2,0xc2       # c0001
  0x80060613,  // addi a2,a2,-2048  # c0800
  0x30061073,  // csrw mstatus,a2

  0x00468693,  // addi a3,a3,0x10 # 8000040
  0x34169073,  // csrw mepc,a3

  0x30251073,  // csrw medeleg, a0

  0x30200073,  // mret

// here:
  0x0000006f,  // j here # spin
  0x0000006f,  // # spin
  0x0000006f,  // # spin
  0x0000006f,  // # spin
};


void init_isa(void) {
  // put initcode to QEMU to setup a PMP to permit access to all of memory in S mode
  bool ok = gdb_memcpy_to_qemu(0x80000000, initcode, sizeof(initcode));
  assert(ok == 1);

  union isa_gdb_regs r;
  gdb_getregs(&r);

  r.pc = 0x80000000;
  ok = gdb_setregs(&r);
  assert(ok == 1);

  // execute enough instructions
  difftest_exec(20);
}
