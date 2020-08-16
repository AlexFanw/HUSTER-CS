#SUBU测试  循环减1   revise date:2018/3/12 tiger
#依次输出  0x00000010 0x0000000f 0x0000000e 0x0000000d 0x0000000c 0x0000000b 0x0000000a 0x00000009 0x00000008 0x00000007 0x00000006 0x00000005 0x00000004 0x00000003 0x00000002 0x00000001 0x00000000 0xffffffff 0xfffffffe 0xfffffffd 0xfffffffc 0xfffffffb 0xfffffffa 0xfffffff9 0xfffffff8 0xfffffff7 0xfffffff6 0xfffffff5 0xfffffff4 0xfffffff3 0xfffffff2 0xfffffff1 0xfffffff0
.text

addi $t0,$zero,1     #
addi $s1,$zero, 0x10     #

add $a0,$0,$s1           
addi $v0,$zero,34         # system call for print
syscall                  # print

addi $t3,$zero, 0x20

subu_branch:
subu $s1,$s1,$t0     #先移1位
add $a0,$0,$s1          
addi $v0,$zero,34         # system call for print
syscall                  # print
addi $t3,$t3, -1    
bne $t3,$zero,subu_branch   #循环8次

addi   $v0,$zero,10         # system call for exit
syscall                  # we are out of here.   
