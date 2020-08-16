#MULTU乘法测试  1111*2*2*2......  revise date:2018/3/12 tiger
#依次输出  0x00001111 0x00002222 0x00004444 0x00008888 0x00011110 0x00022220 0x00044440 0x00088880 0x00111100 0x00222200 0x00444400 0x00888800 0x01111000 0x02222000 0x04444000 0x08888000 0x11110000 0x22220000 0x44440000 0x88880000 0x11100000 0x22200000 0x44400000 0x88800000 0x11000000 0x22000000 0x44000000 0x88000000 0x10000000 0x20000000 0x40000000 0x80000000 0x00000000
.text

addi $t0,$zero,2     #sllv 移位次数
addi $s1,$zero, 0x1111     #

add $a0,$0,$s1           
addi $v0,$zero,34         # system call for print
syscall                  # print

addi $t3,$zero,32  #循环次数
multu_branch:
multu $s1,$t0     #测试指令
mflo $s1          #测试指令
add $a0,$0,$s1          
addi $v0,$zero,34         # system call for print
syscall                  # print
addi $t3,$t3, -1    
bne $t3,$zero,multu_branch   #循环8次

addi   $v0,$zero,10         # system call for exit
syscall                  # we are out of here.   
