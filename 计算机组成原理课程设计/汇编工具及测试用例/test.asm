 .text
  li $s0,0xffff0010
  li $s1,64
  li $s2,6
  sw $s1,($s0)
 
  addi   $v0,$zero,10         # system call for exit
  syscall                  # we are out of here.   
