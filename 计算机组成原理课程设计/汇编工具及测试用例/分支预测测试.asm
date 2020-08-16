#############################################################
#用于BHT表才载入过程测试，LRU淘汰策略测试，BHT表预测功效测试
#############################################################
.text
 addi $s1,$zero, 5   #循环次数
 
 j jmp_next1         #载入BHT,BHT有1个表项 
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
 addi $s4,$zero, 4

jmp_next1:
 j jmp_next2        #载入BHT,BHT有2个表项
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
 addi $s4,$zero, 4
jmp_next2:
 j jmp_next3        #载入BHT,BHT有3个表项,后续会多次执行，应预测成功
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
 addi $s4,$zero, 4
jmp_next3:
 j jmp_next4        #载入BHT,BHT有4个表项,后续会多次执行，应预测成功
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
 addi $s4,$zero, 4

jmp_next4:
 j jmp_next5        #载入BHT,BHT有5个表项,后续会多次执行，应预测成功
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
 addi $s4,$zero, 4

jmp_next5:
 j jmp_next6        #载入BHT,BHT有6个表项,后续会多次执行，应预测成功
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
 addi $s4,$zero, 4
 
 jmp_next6:
 j jmp_next7        #载入BHT,BHT有7个表项,后续会多次执行，应预测成功
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
 addi $s4,$zero, 4

jmp_next7:
 j jmp_next8        #载入BHT,BHT有8个表项,后续会多次执行，应预测成功
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
 addi $s4,$zero, 4

jmp_next8:
 addi $s1,$s1, -1    
 bne $s1,$0, jmp_next2   
 
 #载入BHT,BHT满，应淘汰 j jmp_next1，后续多次执行，跳转有成功有失败

 addi $s0,$zero,1
 addi $s2,$zero,255
 addi $s1,$zero,1
 addi $s3,$zero,3

 beq $s0, $s2, jmp_next9   #载入BHT,BTH已满，淘汰j jmp_next2 
 beq $s0, $s0, jmp_next9   #载入BHT,BTH已满，淘汰j jmp_next3 

 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
 addi $s4,$zero, 4

jmp_next9:
 bne $s1, $s1, jmp_next10   #载入BHT,BTH已满，淘汰j jmp_next4 
 bne $s1, $s2, jmp_next10   #载入BHT,BTH已满，淘汰j jmp_next5

 addi $s1,$zero,1    #不会执行
 addi $s2,$zero,2
 addi $s3,$zero,3

jmp_next10:
 
 jal func            #载入BHT,BTH已满，淘汰j jmp_next6

 addi   $v0,$zero,10      
 syscall                  #程序退出，停机

func: addi $s0,$zero, 0     #子函数
       addi $s0,$s0, 1
       add    $a0,$0,$s0      
       addi   $v0,$0,34        
       syscall                 
       jr $31           #载入BHT,BTH已满，淘汰j jmp_next7