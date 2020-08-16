#XOR测试    revise date:2018/3/12 tiger
# 0x00007777 xor   0xffffffff =  0xffff8888 
# 0xffff8888 xor   0xffffffff =  0x00007777 
#依次输出 0x00007777 0xffff8888 0x00007777 0xffff8888 0x00007777 0xffff8888 0x00007777 0xffff8888 0x00007777 0xffff8888 0x00007777 0xffff8888 0x00007777 0xffff8888 0x00007777 0xffff8888 0x00007777

.text

addi $t0,$zero,-1     #
addi $s1,$zero, 0x7777     #

add $a0,$0,$s1           
addi $v0,$zero,34         # system call for print
syscall                  # print

addi $t3,$zero, 0x10

xor_branch:
xor $s1,$s1,$t0     #先移1位
add $a0,$0,$s1          
addi $v0,$zero,34         # system call for print
syscall                  # print
addi $t3,$t3, -1    
bne $t3,$zero,xor_branch   #循环8次

addi   $v0,$zero,10         # system call for exit
syscall                  # we are out of here.   
