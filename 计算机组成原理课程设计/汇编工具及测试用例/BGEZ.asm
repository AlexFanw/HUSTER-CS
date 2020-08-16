#bgez 测试    大于等于零跳转   递减运算 ，从正数开始向零运算revise date:2018/3/12 tiger  
#依次输出0x0000000f 0x0000000e 0x0000000d 0x0000000c 0x0000000b 0x0000000a 0x00000009 0x00000008 0x00000007 0x00000006 0x00000005 0x00000004 0x00000003 0x000000020 x000000010 x00000000
.text
addi $s1,$zero,15  #初始值
bgez_branch:
add $a0,$0,$s1          
addi $v0,$zero,34         
syscall                  # 输出当前值
addi $s1,$s1,-1
bgez $s1,bgez_branch   #测试指令

addi   $v0,$zero,10         #停机指令
syscall                  # 系统调用
