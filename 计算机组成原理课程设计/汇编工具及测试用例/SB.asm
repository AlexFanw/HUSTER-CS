#SB 测试    revise date:2018/3/14 tiger
#依次输出   0x00000000 0x00000001 0x00000002 0x00000003 0x00000004 0x00000005 0x00000006 0x00000007 0x00000008 0x00000009 0x0000000a 0x0000000b 0x0000000c 0x0000000d 0x0000000e 0x0000000f 0x00000010 0x00000011 0x00000012 0x00000013 0x00000014 0x00000015 0x00000016 0x00000017 0x00000018 0x00000019 0x0000001a 0x0000001b 0x0000001c 0x0000001d 0x0000001e 0x0000001f 0x03020100 0x07060504 0x0b0a0908 0x0f0e0d0c 0x13121110 0x17161514 0x1b1a1918 0x1f1e1d1c
.text

addi $t1,$zero,0     #init_addr 
addi $t3,$zero,32     #counter

#sb写入 01,02,03,04
addi $s1,$zero, 0x00  #
addi $s2,$zero, 0x01  #

sb_store:
sb $s1,($t1)
add $a0,$0,$s1          
addi $v0,$zero,34        # system call for print
syscall                  # print

add $s1,$s1,$s2          #data +1
addi $t1,$t1,1           # addr ++  
addi $t3,$t3,-1          #counter
bne $t3,$zero,sb_store

addi $t3,$zero,8
addi $t1,$zero,0    # addr   
sb_branch:
lw $s1,($t1)       #读出数据 
add $a0,$0,$s1          
addi $v0,$zero,34        # system call for print
syscall                  # print
addi $t1,$t1,4    
addi $t3,$t3, -1    
bne $t3,$zero,sb_branch

addi   $v0,$zero,10      # system call for exit
syscall                  # we are out of here.   
