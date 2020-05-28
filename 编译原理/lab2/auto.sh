screenfetch
rm lex.yy.c
rm parser.tab.c
rm parser.tab.h
rm parser
flex Vector.l
echo "FLEX运行完毕"
bison -d -v parser.y
echo "BISON运行完毕"
gcc -o parser lex.yy.c parser.tab.c ast.c semantic.c
echo "GCC连接完毕"
./parser test.c > result.log
echo "语义检查完成"