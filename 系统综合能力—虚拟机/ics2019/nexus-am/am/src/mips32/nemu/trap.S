
#define MAP(c, f) c(f)

#define REGS(f) \
      f( 1) f( 2) f( 3) f( 4) f( 5) f( 6) f( 7) f( 8) f( 9) \
f(10) f(11) f(12) f(13) f(14) f(15) f(16) f(17) f(18) f(19) \
f(20) f(21) f(22) f(23) f(24) f(25)             f(28)       \
f(30) f(31)

#define PUSH(n) sw $n, (n * 4)($sp);
#define POP(n)  lw $n, (n * 4)($sp);

#define CONTEXT_SIZE ((31 + 6) * 4)
#define OFFSET_SP     (29 * 4)
#define OFFSET_LO     (32 * 4)
#define OFFSET_HI     (33 * 4)
#define OFFSET_CAUSE  (34 * 4)
#define OFFSET_STATUS (35 * 4)
#define OFFSET_EPC    (36 * 4)

#define CP0_STATUS 12
#define CP0_CAUSE  13
#define CP0_EPC    14

.set noat
.globl __am_asm_trap
__am_asm_trap:
  move $k0, $sp
  addiu $sp, $sp, -CONTEXT_SIZE

  MAP(REGS, PUSH)

  sw $k0, OFFSET_SP($sp)
  mflo $t0
  mfhi $t1
  mfc0 $t2, $CP0_CAUSE
  mfc0 $t3, $CP0_STATUS
  mfc0 $t4, $CP0_EPC
  sw $t0, OFFSET_LO($sp)
  sw $t1, OFFSET_HI($sp)
  sw $t2, OFFSET_CAUSE($sp)
  sw $t3, OFFSET_STATUS($sp)
  sw $t4, OFFSET_EPC($sp)

  # allow nested exception
  li $a0, ~0x3
  and $t3, $t3, $a0  # clear status.exl and status.ie
  mtc0 $t3, $CP0_STATUS

  move $a0, $sp
  jal __am_irq_handle

  lw $t0, OFFSET_LO($sp)
  lw $t1, OFFSET_HI($sp)
  lw $t3, OFFSET_STATUS($sp)
  lw $t4, OFFSET_EPC($sp)

  # set status.exl
  ori $t3, $t3, 0x2

  mtlo $t0
  mthi $t1
  mtc0 $t3, $CP0_STATUS
  mtc0 $t4, $CP0_EPC

  MAP(REGS, POP)

  addiu $sp, $sp, CONTEXT_SIZE

  eret
