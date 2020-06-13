+ # 编译原理实验

	> 自定义语言名：Vector

	### 实验三: 中间代码生成

编译环境：macOS Catalina
编译过程：详情请见auto.sh, shell脚本代码如下

```shell
screenfetch
rm lex.yy.c
rm parser.tab.c
rm parser.tab.h
rm parser
flex Vector.l
echo "编译原理实验三 U201714670 范唯 CS1703"
echo "FLEX运行完毕"
bison -d -v parser.y
echo "BISON运行完毕"
gcc -o parser ast.c analysis.c parser.tab.c lex.yy.c  blocks.c optimize.c -w
echo "GCC连接完毕"
./parser test.c
echo "语义检查完成"
```

**文件说明：**

+ parser 为可执行程序
+ code.txt 为最开始生成的中间代码
+ temp.txt 为优化途中生成的中间代码
+ optimized.txt 为最终优化好的中间代码

> 其余文件不再赘述



**实验完成情况：**

+ 数组 for char break continue(支持嵌套)以及复合赋值语句的中间代码生成

+ 基本块的划分

+ 对中间代码进行了简单的优化，包括删除死代码，删除中间变量，以及进行简单的算数优化(如果赋值表达式的2个操作数为立即数，可以直接求值优化成赋值语句；如果是乘法除法语句，并且是2的整数次幂，优化成移位运算)

