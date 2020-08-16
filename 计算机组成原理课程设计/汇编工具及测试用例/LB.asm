#LB测试    revise date:2018/3/12 tiger
#依次输出 0xffffff81 0xffffff82 0xffffff83 0xffffff84 0xffffff85 0xffffff86 0xffffff87 0xffffff88 0xffffff89 0xffffff8a 0xffffff8b 0xffffff8c 0xffffff8d 0xffffff8e 0xffffff8f 0xffffff90 0xffffff91 0xffffff92 0xffffff93 0xffffff94 0xffffff95 0xffffff96 0xffffff97 0xffffff98 0xffffff99 0xffffff9a 0xffffff9b 0xffffff9c 0xffffff9d 0xffffff9e 0xffffff9f 0xffffffa0
.text
addi $t1,$zero,0     #init_addr 
addi $t3,$zero,16     #counter

#预先写入数据，实际是按字节顺序存入 0x81,82,84,86,87,88,89.......等差数列
ori $s1,$zero, 0x8483  #
addi $s2,$zero, 0x0404  #
sll $s1,$s1,16
sll $s2,$s2,16
ori $s1,$s1, 0x8281  #    注意一般情况下MIPS采用大端方式
addi $s2,$s2, 0x0404  #   init_data= 0x84838281 next_data=init_data+ 0x04040404
lb_store:
sw $s1,($t1)
add $s1,$s1,$s2   #data +1
addi $t1,$t1,4    # addr +4  
addi $t3,$t3,-1   #counter
bne $t3,$zero,lb_store

addi $t3,$zero,32   #循环次数
addi $t1,$zero,0    # addr 
lb_branch:
lb $s1,($t1)         #测试指令
add $a0,$0,$s1          
addi $v0,$zero,34         #输出
syscall                  
addi $t1,$t1, 1    
addi $t3,$t3, -1    
bne $t3,$zero,lb_branch



addi   $v0,$zero,10         # system call for exit
syscall                  # we are out of here.   
