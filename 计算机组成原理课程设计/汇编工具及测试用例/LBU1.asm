#LBU 测试    revise date:2018/3/12 tiger#
#依次输出   0x00000081 0x00000082 0x00000083 0x00000084 0x00000085 0x00000086 0x00000087 0x00000088 0x00000089 0x0000008a 0x0000008b 0x0000008c 0x0000008d 0x0000008e 0x0000008f 0x00000090 0x00000091 0x00000092 0x00000093 0x00000094 0x00000095 0x00000096 0x00000097 0x00000098 0x00000099 0x0000009a 0x0000009b 0x0000009c 0x0000009d 0x0000009e 0x0000009f 0x000000a0
.text
addi $t1,$zero,0     #init_addr 
addi $t3,$zero,32     #counter

#预先写入数据，实际是按字节顺序存入 0x81,82,84,86,87,88,89.......等差数列
ori $s1,$zero, 0x8483  #
addi $s2,$zero, 0x0401  #
sll $s1,$s1,16
sll $s2,$s2,16
ori $s1,$s1, 0x8281  #    注意一般情况下MIPS采用大端方式
addi $s2,$s2, 0x0401  #   init_data= 0x84838281 next_data=init_data+ 0x04040404

lbu_store:
sw $s1,($t1)
add $s1,$s1,$s2   #data +1
addi $t1,$t1,4    # addr +4  
addi $t3,$t3,-1   #counter
bne $t3,$zero,lbu_store

addi $v0,$zero,34    #init_$2
addi $t3,$zero,32
addi $t1,$zero,0    # addr +4  
lbu_branch:
lbu $s1,($t1)     #测试指令
add $a0,$0,$s1          
addi $v0,$zero,34         
syscall                  # 输出
addi $t1,$t1, 4    
addi $t3,$t3, -1    
bne $t3,$zero,lbu_branch

addi   $v0,$zero,10         # system call for exit
syscall                  # we are out of here.   
