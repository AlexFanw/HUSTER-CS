#SRLV移位测试    revise date:2018/3/14 tiger
#依次输出  0x87600000 0x08760000 0x00876000 0x00087600 0x00008760 0x00000876 0x00000087 0x00000008 0x00000000
.text

addi $t0,$zero,1     #sllv 移位次数
addi $t1,$zero,3     #sllv 移位次数
addi $s1,$zero, 0x876     #
sll $s1,$s1,20     #

add $a0,$0,$s1           
addi $v0,$zero,34         # system call for print
syscall                  # print

addi $t3,$zero,8

srlv_branch:
srlv $s1,$s1,$t0     #先移1位
srlv $s1,$s1,$t1     #再移3位
add $a0,$0,$s1          
addi $v0,$zero,34         # system call for print
syscall                  # print
addi $t3,$t3, -1    
bne $t3,$zero,srlv_branch   #循环8次

addi   $v0,$zero,10         # system call for exit
syscall                  # we are out of here.   
