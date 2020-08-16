#############################################################
#测试j,jal,jr指令，如需要可分开测试，执行正常应该是15个周期 revise date 2015/12/17 tiger
#############################################################
.text
 addi $s1,$zero, 1   #测试j,jal,jr指令，如需要可分开测试，执行正常应该是15个周期
 j jmp_next1
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
jmp_next1:
 j jmp_next2
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
jmp_next2:
 j jmp_next3
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
jmp_next3:
 j jmp_next4
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
jmp_next4:jal jmp_count

######################################


#移位测试  需要支持超addi,sll,add,syscall,srl,sll,sra,beq,j,syscall    revise date:2015/12/16 tiger

.text
addi $s0,$zero,1     #简单移位，循环测试，0号区域显示的是初始值1左移1位重复15次的值，1号区域是累加值
addi $s1,$zero,1  
sll $s1, $s1, 31   #逻辑左移31位 $s1=0x80000000
 

###################################################################
#                逻辑右移测试 
# 显示区域依次显示0x80000000 0x20000000 0x08000000 0x02000000 0x00800000 0x00200000 0x00080000 0x00020000 0x00008000 0x00002000 0x00000800 0x00000200 0x00000080 0x00000020 0x00000008 0x00000002 0x00000000  
###################################################################
LogicalRightShift:            #逻辑右移测试，将最高位1逐位向右右移直至结果为零

add    $a0,$0,$s1       #display $s1    #逻辑右移测试，将最高位1逐位向右右移直至结果为零
addi   $v0,$0,34        # display hex
syscall                 # we are out of here.  
     
srl $s1, $s1, 2   
beq $s1, $zero, shift_next1
j LogicalRightShift

shift_next1:

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  


###################################################################
#                逻辑左移测试 
# 显示区域依次显示0x00000004 0x00000010 0x00000040 0x00000100 0x00000400 0x00001000 0x00004000 0x00010000 0x00040000 0x00100000 0x00400000 0x01000000 0x04000000 0x10000000 0x40000000 0x00000000 
###################################################################

addi $s1,$zero, 1        #                逻辑左移测试 
LogicalLeftShift:         #逻辑左移测试，将最低位1逐位向左移直至结果为零
sll $s1, $s1, 2  

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  
      
beq $s1, $zero, ArithRightShift
j LogicalLeftShift


###################################################################
#                算术右移测试 
# 显示区域依次显示0x80000000 0xf0000000 0xff000000 0xfff00000 0xffff0000 0xfffff000 0xffffff00 0xfffffff0 0xffffffff 
###################################################################
ArithRightShift:          #算术右移测试，#算术移位测试，80000000算术右移，依次显示为F0000000,FF000000,FFF00000,FFFF0000直至FFFFFFFF

addi $s1,$zero,1     #                算术右移测试 
sll $s1, $s1, 31   #逻辑左移31位 $s1=0x80000000

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  

sra $s1, $s1, 3    #$s1=0X80000000-->0XF0000000

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  


sra $s1, $s1, 4    #0XF0000000-->0XFF000000

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  


sra $s1, $s1, 4    #0XFF000000-->0XFFF00000

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  

sra $s1, $s1, 4    

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  

sra $s1, $s1, 4    

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  


sra $s1, $s1, 4    

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  


sra $s1, $s1, 4    

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  


sra $s1, $s1, 4    


add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  

#############################################################
#走马灯测试,测试addi,andi,sll,srl,sra,or,ori,nor,syscall  LED按走马灯方式来回显示数据
#############################################################

.text
addi $s0,$zero,1 
sll $s3, $s0, 31      # $s3=0x80000000
sra $s3, $s3, 31      # $s3=0xFFFFFFFF   
addu $s0,$zero,$zero   # $s0=0         
addi $s2,$zero,12 

addiu $s6,$0,3  #走马灯计数
zmd_loop:

addiu $s0, $s0, 1    #计算下一个走马灯的数据
andi $s0, $s0, 15  

#######################################
addi $t0,$0,8    
addi $t1,$0,1
left:

sll $s3, $s3, 4   #走马灯左移
or $s3, $s3, $s0

add    $a0,$0,$s3       # display $s3
addi   $v0,$0,34         # system call for LED display 
syscall                 # display 

sub $t0,$t0,$t1
bne $t0,$0,left
#######################################

addi $s0, $s0, 1   #计算下一个走马灯的数据
addi $t8,$0,15
and $s0, $s0, $t8
sll $s0, $s0, 28     

addi $t0,$0,8
addi $t1,$0,1

zmd_right:

srl $s3, $s3, 4  #走马灯右移
or $s3, $s3, $s0

addu    $a0,$0,$s3       # display $s3
addi   $v0,$0,34         # system call for LED display 
syscall                 # display 

sub $t0,$t0,$t1
bne $t0,$0,zmd_right
srl $s0, $s0, 28  
#######################################

sub $s6,$s6,$t1
beq $s6,$0, exit
j zmd_loop

exit:

add $t0,$0,$0
nor $t0,$t0,$t0      #test nor  ori
sll $t0,$t0,16
ori $t0,$t0,0xffff

addu   $a0,$0,$t0       # display $t0
addi   $v0,$0,34         # system call for LED display 
syscall                 # display 
#################################################################################
#本程序实现0-15号字单元的降序排序,此程序可在mars mips仿真器中运行
#运行时请将Mars Setting中的Memory Configuration设置为Compact，data at address 0
#
#################################################################################
 .text
sort_init:
 addi $s0,$0,-1
 addi $s1,$0,0
 
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
    sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
   
 addi $s0,$s0,1
 
 add $s0,$zero,$zero   
 addi $s1,$zero,60   #排序区间
sort_loop:
 lw $s3,0($s0)     
 lw $s4,0($s1)
 slt $t0,$s3,$s4
 beq $t0,$0,sort_next   #降序排序
 sw $s3, 0($s1)
 sw $s4, 0($s0)   
sort_next:
 addi $s1, $s1, -4   
 bne $s0, $s1, sort_loop  
 
 add    $a0,$0,$s0       #display $s0
 addi   $v0,$0,34         # display hex
 syscall                 # we are out of here.  DISP: disp $r0, 0
 
 addi $s0,$s0,4
 addi $s1,$zero,60
 bne $s0, $s1, sort_loop

 addi   $v0,$zero,50         # system call for exit
 syscall                  # we are out of here.   
 #MIPS处理器实现中请用停机指令实现syscall

jmp_count: addi $s0,$zero, 0
       addi $s0,$s0, 1
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  
       
       addi $s0,$s0, 2
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  
       
       addi $s0,$s0, 3
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  
       
       addi $s0,$s0, 4       
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  
       
       addi $s0,$s0, 5              
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  
       
       addi $s0,$s0, 6              
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  

       addi $s0,$s0, 7              
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  

       addi $s0,$s0, 8              
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       addi   $v0,$0,34         # display hex       
       syscall                 # we are out of here.  

       
       jr $31
