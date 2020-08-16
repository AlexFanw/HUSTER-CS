#LUI≤‚ ‘    revise date:2018/3/12 tiger
#“¿¥Œ ‰≥ˆ 0xfedcffff 0xba980000 0x76540000 0x32100000 0xfedcffff 0xba980000 0x76540000 0x32100000 0xfedcffff 0xba980000 0x76540000 0x32100000 0xfedcffff 0xba980000 0x76540000 0x32100000 0xfedcffff 0xba980000 0x76540000 0x32100000 0xfedcffff 0xba980000 0x76540000 0x32100000 0xfedcffff 0xba980000 0x76540000 0x32100000 0xfedcffff 0xba980000 0x76540000 0x32100000

.text

addi $t3,$zero,  0x8

lui_branch:
lui $s1,  0xFEDC 
ori $s1,$s1, 0xffff
add $a0,$0,$s1          
addi $v0,$zero,34         # system call for print
syscall    
lui $s1,  0xBA98
add $a0,$0,$s1          
syscall    
lui $s1,  0x7654     
add $a0,$0,$s1          
syscall    
lui $s1,  0x3210     
add $a0,$0,$s1          
syscall    
                           # print
addi $t3,$t3, -1    
bne $t3,$zero,lui_branch

addi   $v0,$zero,10         # system call for exit
syscall                  # we are out of here.   
