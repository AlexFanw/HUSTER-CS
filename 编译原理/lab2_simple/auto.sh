rm lex.yy.c
rm parser.tab.c
rm parser.tab.h
rm parser
flex lex.l
echo "FLEX运行完毕"
bison -d -v parser.y
echo "BISON运行完毕"
gcc -o parser lex.yy.c parser.tab.c ast.c analysis.c
echo "GCC连接完毕"
echo "执行的文件名:$0"
./parser $1
echo "编译完成:$1"