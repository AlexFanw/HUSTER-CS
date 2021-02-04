.global __am_ret_from_trap
.global __am_asm_trap

__am_asm_trap:
  # getcontext() does not preserve %rax, save it manually
  pushq %rax
  pushq %rdi
  # must have sizeof(ucontect_t) < 1024
  subq $1024, %rsp

  movq %rsp, %rdi
  call __am_irq_handle

__am_ret_from_trap:

  addq $1024, %rsp
  popq %rdi
  popq %rax
  retq
