#SLLV“∆Œª≤‚ ‘    revise date:2018/3/12 tiger
#“¿¥Œ ‰≥ˆ  0x00000876 0x00008760 0x00087600 0x00876000 0x08760000 0x87600000 0x76000000 0x60000000 0x00000000

.text

addi $t0,$zero,1     
addi $t1,$zero,3     
addi $s1,$zero,  0x876     

add $a0,$0,$s1           
addi $v0,$zero,34         # system call for print
syscall                  # print

addi $t3,$zero,8

sllv_branch:
sllv $s1,$s1,$t0     #≤‚ ‘÷∏¡Ó
sllv $s1,$s1,$t1     #≤‚ ‘÷∏¡Ó
add $a0,$0,$s1          
addi $v0,$zero,34         # system call for print
syscall                  # print
addi $t3,$t3, -1    
bne $t3,$zero,sllv_branch

addi   $v0,$zero,10         # system call for exit
syscall                  # we are out of here.   
