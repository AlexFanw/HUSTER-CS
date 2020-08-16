# include 16 instructions : 5 R type ,11 I type.
# benchmark for beq and bne inst instructions
.text
addi $s0,$zero,1
addi $s2,$zero,255
addi $s1,$zero,1
addi $s3,$zero,3
beq $s0, $s2, Next1
beq $s0, $s0, Next1
addi $s1,$zero,1    # can not execute
addi $s2,$zero,2
addi $s3,$zero,3

Next1:
 add    $a0,$0,$s0       # display $s0
 addi   $v0,$0,34         # system call for display
 syscall                 # syscall include 2 hidden operand: $v0,$a0£¬may cause data hazzard

 bne $s1, $s1, Next2
 bne $s1, $s2, Next2

 addi $s1,$zero,1    # can not execute
 addi $s2,$zero,2
 addi $s3,$zero,3

Next2:
 add    $a0,$0,$s3       # display $s0
 addi   $v0,$0,34        # system call for display
 syscall                 # syscall include 2 hidden operand: $v0,$a0£¬may cause data hazzard

 addi   $v0,$zero,10      # system call for exit
 syscall                  # we are out of here.   

