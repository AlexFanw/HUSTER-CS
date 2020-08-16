#SH ≤‚ ‘    revise date:2018/3/14 tiger
#“¿¥Œ ‰≥ˆ 0x00000001 0x00000002 0x00000003 0x00000004 0x00000005 0x00000006 0x00000007 0x00000008 0x00000009 0x0000000a 0x0000000b 0x0000000c 0x0000000d 0x0000000e 0x0000000f 0x00000010 0x00000011 0x00000012 0x00000013 0x00000014 0x00000015 0x00000016 0x00000017 0x00000018 0x00000019 0x0000001a 0x0000001b 0x0000001c 0x0000001d 0x0000001e 0x0000001f 0x00000020 0x00020001 0x00040003 0x00060005 0x00080007 0x000a0009 0x000c000b 0x000e000d 0x0010000f 0x00120011 0x00140013 0x00160015 0x00180017 0x001a0019 0x001c001b 0x001e001d 0x0020001f

.text

addi $t1,$zero,0     #init_addr 
addi $t3,$zero,32     #counter

#SH–¥»Î 01,02,03,04
addi $s1,$zero, 0x0001  #
addi $s2,$zero, 0x01  #
sh_store:
sh $s1,($t1)
add $a0,$0,$s1          
addi $v0,$zero,34         # system call for print
syscall                  # print

add $s1,$s1,$s2   #data +1
addi $t1,$t1,2    # addr +4  
addi $t3,$t3,-1   #counter
bne $t3,$zero,sh_store


addi $t3,$zero,16
addi $t1,$zero,0    # addr 
sh_branch:
lw $s1,($t1)     
add $a0,$0,$s1          
addi $v0,$zero,34         # system call for print
syscall                  # print
addi $t1,$t1,4    
addi $t3,$t3, -1    
bne $t3,$zero,sh_branch

addi   $v0,$zero,10         # system call for exit
syscall                  # we are out of here.   
