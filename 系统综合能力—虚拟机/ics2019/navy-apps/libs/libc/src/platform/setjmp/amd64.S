/*
  This file contains setjmp/longjmp for all supported ISAs.
  Refer to https://github.com/bminor/newlib/blob/master/newlib/libc/machine/x86_64/setjmp.S
*/

#ifdef __ISA_AM_NATIVE__
#
# our buffer looks like:
#  rbx,rbp,r12,r13,r14,r15,rsp,rip
.globl  setjmp
setjmp:
  movq  %rbx,  0(%rdi)
  movq  %rbp,  8(%rdi)
  movq  %r12, 16(%rdi)
  movq  %r13, 24(%rdi)
  movq  %r14, 32(%rdi)
  movq  %r15, 40(%rdi)
  leaq  8(%rsp), %rax
  movq  %rax, 48(%rdi)
  movq  (%rsp), %rax
  movq  %rax, 56(%rdi)
  xorq  %rax, %rax
  ret

#
# our buffer looks like:
#  rbx,rbp,r12,r13,r14,r15,rsp,rip
#
# _longjmp is called with two parameters:  jmp_buf*,int
# jmp_buf* is at %rdi, int is at %rsi

.globl  longjmp
longjmp:
  movq   %rsi, %rax        /* Return value */
  
  movq     8 (%rdi), %rbp
  
  movq    48 (%rdi), %rsp
  pushq   56 (%rdi)
  movq     0 (%rdi), %rbx
  movq    16 (%rdi), %r12
  movq    24 (%rdi), %r13
  movq    32 (%rdi), %r14
  movq    40 (%rdi), %r15

  testq  %rax, %rax
  jne  bye
  incq  %rax    # rax hold 0 if we are here
bye:
  ret
#endif
