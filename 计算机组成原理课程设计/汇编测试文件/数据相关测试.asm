#用于数据相关性测试，程序最终完成等差数列求和部分运算，38条指令
.text

addi $s1, $0, 4
sw $s1, 0($s1)     
lw $s2, 0($s1)    
addi $s2,$s2,-4   #s2 address      #load-use相关
addi $s0,$0,0     #数列初值
addi $s1,$s0,1     #计算下一个数，等差值为1    和上条指令相关
add $s0,$s0,$s1    #求累加和   和上上条指令相关
add $s2,$s2,4      #地址累加    
sw $s0,0($s2)      #存累加和
addi $s1,$s1,1
add $s0,$s0,$s1    #求累加和
add $s2,$s2,4      #地址累加    
sw $s0,0($s2)      #存累加和
addi $s1,$s1,1
add $s0,$s0,$s1    #求累加和
add $s2,$s2,4      #地址累加    
sw $s0,0($s2)      #存累加和
addi $s1,$s1,1
add $s0,$s0,$s1    #求累加和
add $s2,$s2,4      #地址累加    
sw $s0,0($s2)      #存累加和
addi $s1,$s1,1
add $s0,$s0,$s1   #求累加和
add $s2,$s2,4      #地址累加    
sw $s0,0($s2)      #存累加和
addi $s1,$s1,1
add $s0,$s0,$s1   #求累加和
add $s2,$s2,4      #地址累加    
sw $s0,0($s2)      #存累加和
addi $s1,$s1,1
add $s0,$s0,$s1   #求累加和
add $s2,$s2,4      #地址累加    
sw $s0,0($s2)      #存累加和

addi $v0,$zero,10         # system call for exit
addi $s0,$zero, 0            #消除相关性
addi $s0,$zero, 0
addi $s0,$zero, 0
syscall                   # we are out of here.   
