#ifdef __ISA_X86__
#
# our buffer looks like:
#  eax,ebx,ecx,edx,esi,edi,esp,ebp,pc
.globl  setjmp
setjmp:
  pushl  %ebx
  movl  8(%esp), %ebx
  movl  %eax, (%ebx)
  popl  %eax
  movl  %eax, 4(%ebx)
  movl  %ecx, 8(%ebx)
  movl  %edx, 12(%ebx)
  movl  %esi, 16(%ebx)
  movl  %edi, 20(%ebx)
  movl  %esp, 24(%ebx)
  movl  %ebp, 28(%ebx)
  movl  (%esp), %eax
  movl  %eax, 32(%ebx)
  movl -4(%esp), %ebx # EBX is caller saved!
  xorl  %eax, %eax
  ret

#
# our buffer looks like:
#  eax,ebx,ecx,edx,esi,edi,esp,ebp,pc
#
# _longjmp is called with two parameters:  jmp_buf*,int
# jmp_buf* is at 4(%esp), int is at 8(%esp)
# retaddr is, of course, at (%esp)

.globl  longjmp
longjmp:
  movl  4(%esp), %ebx  # address of buf
  movl  8(%esp), %eax  # store return value

  movl  24(%ebx), %esp  # restore stack
  movl  32(%ebx), %edi
# Next line sets up return address.
  movl  %edi, 0(%esp)  
  movl  8(%ebx), %ecx
  movl  12(%ebx), %edx
  movl  16(%ebx), %esi
  movl  20(%ebx), %edi
  movl  28(%ebx), %ebp
  movl  4(%ebx), %ebx
  testl  %eax,%eax
  jne  bye
  incl  %eax    # eax hold 0 if we are here
bye:
  ret
#endif
