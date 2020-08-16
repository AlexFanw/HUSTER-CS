#bltz 测试    小于0跳转   累加运算，从负数开始向零运算 revise date:2018/3/12 tiger  
#依次输出0xfffffff1 0xfffffff2 0xfffffff3 0xfffffff4 0xfffffff5 0xfffffff6 0xfffffff7 0xfffffff8 0xfffffff9 0xfffffffa 0xfffffffb 0xfffffffc 0xfffffffd 0xfffffffe 0xffffffff
.text
addi $s1,$zero,-15       #初始值
bltz_branch:
add $a0,$0,$s1          
addi $v0,$zero,34         
syscall                  #输出当前值
addi $s1,$s1,1 
bltz $s1,bltz_branch     #当前指令


addi   $v0,$zero,10    
syscall                  #暂停或退出
