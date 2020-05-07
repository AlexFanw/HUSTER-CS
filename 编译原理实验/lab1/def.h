#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"
#include "parser.tab.h"
#define MAXLENGTH   200
#define DX 3*sizeof(int)          /*活动记录控制信息需要的单元数，这个根据实际系统调整*/
//以下语法树结点类型、三地址结点类型等定义仅供参考，实验时一定要根据自己的理解来定义
int LEV;      //层号
struct opn{
    int kind;    //标识联合成员的属性
    int type;    //标识操作数的数据类型
    union {
        int     const_int;      //整常数值，立即数
        float   const_float;    //浮点常数值，立即数
        char    const_char;     //字符常数值，立即数
        char    id[33];         //变量或临时变量的别名或标号字符串
        };
    int level;                  //变量的层号，0表示是全局变量，数据保存在静态数据区
    int offset;                 //偏移量，目标代码生成时用
    };

struct codenode {   //三地址TAC代码结点,采用单链表存放中间语言代码
        int  op;
        struct opn opn1,opn2,result;
        struct codenode  *next,*prior;
    };

struct ASTNode {
        //以下对结点属性定义没有考虑存储效率，只是简单地列出要用到的一些属性
	int kind;
	union {
		  char type_id[33];             //由标识符生成的叶结点
		  int type_int;                 //由整常数生成的叶结点
		  float type_float;               //由浮点常数生成的叶结点
          char type_char;
          char type_string[33];
	      };
    struct ASTNode *ptr[4];         //由kind确定有多少棵子树
    int place;                     //存放（临时）变量在符号表的位置序号
    char Etrue[15],Efalse[15];       //对布尔表达式的翻译时，真假转移目标的标号
    char Snext[15];               //结点对应语句S执行后的下一条语句位置标号
    struct codenode *code;          //该结点中间代码链表头指针
    int type;                      //用以标识表达式结点的类型
    int pos;                       //语法单位所在位置行号
    int offset;                     //偏移量
    int width;                     //占数据字节数
    int num;                      //计数器，可以用来统计形参个数
    };

struct symbol {       //这里只列出了一个符号表项的部分属性，没考虑属性间的互斥
    char name[33];   //变量或函数名
    int level;        //层号
    int type;         //变量类型或函数返回值类型
    int  paramnum;  //对函数适用，记录形式参数个数
    char alias[10];   //别名，为解决嵌套层次使用
    char flag;       //符号标记，函数：'F'  变量：'V'   参数：'P'  临时变量：'T'
char offset;      //外部变量和局部变量在其静态数据区或活动记录中的偏移量，
//或记录函数活动记录大小，目标代码生成时使用
    //函数入口等实验可能会用到的属性...
    };
//符号表
struct symboltable{
    struct symbol symbols[MAXLENGTH];
    int index;
    } symbolTable;

struct symbol_scope_begin {
    //当前作用域的符号在符号表的起始位置序号,这是一个栈结构,当使用顺序表作为符号表时，进入、退出一个作用域时需要对其操作，以完成符号表的管理。对其它形式的符号表，不一定需要此数据结构
    int TX[30];
    int top;
    } symbol_scope_TX;


struct ASTNode * mknode(int num,int kind,int pos,...);
void semantic_Analysis0(struct ASTNode *T);
void semantic_Analysis(struct ASTNode *T);
void boolExp(struct ASTNode *T);
void Exp(struct ASTNode *T);
void objectCode(struct codenode *head);
void displayArrayExp(struct ASTNode * T);


