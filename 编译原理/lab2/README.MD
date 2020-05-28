## Lab2 语义分析

编译环境：ubuntu 18.04.3 LTS 64-bit
内核版本： 4.18.9
编译过程
```SHELL
flex lex.l
bison -d -v parser.y
gcc ast.c analysis.c parser.tab.c lex.yy.c -lfl -o test
./test test.c > log.log ## test.c为测试代码 输出见log.log
```

实验完成情况：
+ 符号表设计
+ 语义错误定义
+ 语义错误检查