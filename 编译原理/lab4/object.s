.data
_Prompt: .asciiz "Enter an integer:  "
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0,4
  la $a0,_Prompt
  syscall
  li $v0,5
  syscall
  jr $ra
write:
  li $v0,1
  syscall
  li $v0,4
  la $a0,_ret
  syscall
  move $v0,$0
  jr $ra

max:
  lw $t1, 12($sp)
  lw $t2, 16($sp)
  bgt $t1,$t2,label2
  j label3
label2:
  lw $v0,12($sp)
  jr $ra
  j label1
label3:
  lw $v0,16($sp)
  jr $ra
label1:

main:
  addi $sp, $sp, -108
  li $t3, 1
  sw $t3, 16($sp)
  lw $t1, -340918068($sp)
  move $t3, $t1
  sw $t3, 0($sp)
  li $t3, 2
  sw $t3, 24($sp)
  lw $t1, -340918068($sp)
  move $t3, $t1
  sw $t3, 0($sp)
  li $t3, 3
  sw $t3, 32($sp)
  lw $t1, -340918068($sp)
  move $t3, $t1
  sw $t3, 0($sp)
  li $t3, 4
  sw $t3, 40($sp)
  lw $t1, -340918068($sp)
  move $t3, $t1
  sw $t3, 0($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal read
  lw $ra,0($sp)
  addi $sp, $sp, 4
  sw $v0, 68($sp)
  lw $t1, 68($sp)
  move $t3, $t1
  sw $t3, 56($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal read
  lw $ra,0($sp)
  addi $sp, $sp, 4
  sw $v0, 68($sp)
  lw $t1, 68($sp)
  move $t3, $t1
  sw $t3, 60($sp)
  move $t0,$sp
  addi $sp, $sp, -20
  sw $ra,0($sp)
  lw $t1, 56($t0)
  move $t3,$t1
  sw $t3,12($sp)
  lw $t1, 60($t0)
  move $t3,$t1
  sw $t3,16($sp)
  jal max
  lw $ra,0($sp)
  addi $sp,$sp,20
  sw $v0,68($sp)
  lw $t1, 68($sp)
  move $t3, $t1
  sw $t3, 64($sp)
  lw $a0, 64($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp, $sp, 4
  li $t3, 1
  sw $t3, 68($sp)
  lw $t1, 68($sp)
  move $t3, $t1
  sw $t3, 44($sp)
  lw $t1, 12($sp)
  lw $t2, 20($sp)
  add $t3,$t1,$t2
  sw $t3, 68($sp)
  lw $t1, 68($sp)
  move $t3, $t1
  sw $t3, 44($sp)
  lw $t1, 12($sp)
  lw $t2, 20($sp)
  add $t3,$t1,$t2
  sw $t3, 68($sp)
  lw $t1, 28($sp)
  lw $t2, 36($sp)
  add $t3,$t1,$t2
  sw $t3, 72($sp)
  lw $t1, 44($sp)
  lw $t2, 72($sp)
  mul $t3,$t1,$t2
  sw $t3, 76($sp)
  lw $t1, 28($sp)
  lw $t2, 36($sp)
  add $t3,$t1,$t2
  sw $t3, 80($sp)
  lw $t1, 76($sp)
  lw $t2, 80($sp)
  mul $t3,$t1,$t2
  sw $t3, 84($sp)
  lw $t1, 68($sp)
  lw $t2, 84($sp)
  sub $t3,$t1,$t2
  sw $t3, 88($sp)
  li $t3, 2
  sw $t3, 92($sp)
  li $t3, 3
  sw $t3, 96($sp)
  lw $t1, 92($sp)
  lw $t2, 96($sp)
  mul $t3,$t1,$t2
  sw $t3, 100($sp)
  lw $t1, 88($sp)
  lw $t2, 100($sp)
  add $t3,$t1,$t2
  sw $t3, 104($sp)
  lw $t1, 104($sp)
  move $t3, $t1
  sw $t3, 48($sp)
label14:
  lw $t1, 12($sp)
  lw $t2, 20($sp)
  blt $t1,$t2,label13
  j label12
label13:
  li $t3, 2
  sw $t3, 68($sp)
  lw $t1, 12($sp)
  lw $t2, 68($sp)
  mul $t3,$t1,$t2
  sw $t3, 72($sp)
  lw $t1, 72($sp)
  lw $t2, 20($sp)
  blt $t1,$t2,label16
  j label15
label16:
  j label14
label15:
  li $t3, 1
  sw $t3, 68($sp)
  lw $t1, 68($sp)
  move $t3, $t1
  sw $t3, 28($sp)
  li $t3, 10
  sw $t3, 80($sp)
  lw $t1, 28($sp)
  lw $t2, 80($sp)
  blt $t1,$t2,label17
  j label14
label18:
  li $t3, 1
  sw $t3, 76($sp)
  lw $t1, 28($sp)
  lw $t2, 76($sp)
  add $t3,$t1,$t2
  sw $t3, 28($sp)
label17:
  li $t3, 5
  sw $t3, 80($sp)
  lw $t1, 28($sp)
  lw $t2, 80($sp)
  blt $t1,$t2,label19
  j label20
label19:
  j label18
  j label18
label20:
  j label14
  j label18
  j label14
label12:
  li $t3, 1
  sw $t3, 68($sp)
  lw $v0,68($sp)
  jr $ra
label4:
