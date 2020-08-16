#xori 测试    revise date:2018/3/12 tiger
# 0x00007777 xor   0x0000ffff =  0x00008888
# 0x00008888  xor   0x0000ffff =  0x00007777 
# 0x00007777 0x00008888 0x00007777 0x00008888 0x00007777 0x00008888 0x00007777 0x00008888 0x00007777 0x00008888 0x00007777 0x00008888 0x00007777 0x00008888 0x00007777 0x00008888 0x00007777

.text

addi $t0,$zero,-1     #
addi $s1,$zero, 0x7777     #


add $a0,$0,$s1           
addi $v0,$zero,34         # system call for print
syscall                  # print

addi $t3,$zero, 0x10

xori_branch:
xori $s1,$s1, 0xffff     #先移1位
add $a0,$0,$s1          
addi $v0,$zero,34         # system call for print
syscall                  # print
addi $t3,$t3, -1    
bne $t3,$zero,xori_branch   #循环8次

addi   $v0,$zero,10         # system call for exit
syscall                  # we are out of here.   
