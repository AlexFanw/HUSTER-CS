
#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)
#define MAP(c, f) c(f)

#define REGS(f) \
      f( 1)       f( 3) f( 4) f( 5) f( 6) f( 7) f( 8) f( 9) \
f(10) f(11) f(12) f(13) f(14) f(15) f(16) f(17) f(18) f(19) \
f(20) f(21) f(22) f(23) f(24) f(25) f(26) f(27) f(28) f(29) \
f(30) f(31)

#define PUSH(n) sw concat(x, n), (n * 4)(sp);
#define POP(n)  lw concat(x, n), (n * 4)(sp);

#define CONTEXT_SIZE ((31 + 4) * 4)
#define OFFSET_SP     ( 2 * 4)
#define OFFSET_CAUSE  (32 * 4)
#define OFFSET_STATUS (33 * 4)
#define OFFSET_EPC    (34 * 4)

.globl __am_asm_trap
__am_asm_trap:
  addi sp, sp, -CONTEXT_SIZE

  MAP(REGS, PUSH)

  mv t0, sp
  addi t0, t0, CONTEXT_SIZE
  sw t0, OFFSET_SP(sp)

  csrr t0, scause
  csrr t1, sstatus
  csrr t2, sepc

  sw t0, OFFSET_CAUSE(sp)
  sw t1, OFFSET_STATUS(sp)
  sw t2, OFFSET_EPC(sp)

  mv a0, sp
  jal __am_irq_handle

  lw t1, OFFSET_STATUS(sp)
  lw t2, OFFSET_EPC(sp)
  csrw sstatus, t1
  csrw sepc, t2

  MAP(REGS, POP)

  addi sp, sp, CONTEXT_SIZE

  sret
