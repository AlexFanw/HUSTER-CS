%error-verbose
%locations
//声明部分
%{
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
int yylex();
void yyerror(const char* fmt, ...);
void display(struct node *,int);
%}

//辅助声明部分,union将各种类型统一起来
/*Bison中默认将所有的语义值都定义为int类型，可以通过定义宏YYSTYPE来改变值的类型。
如果有多个值类型，则需要通过在Bison声明中使用%union列举出所有的类型。*/
%union {
  int type_int;
  float type_float;
  char type_char;
  char type_id[32];
  struct node *ptr;
};

/*
%type定义非终结符的语义值类型 %type <union 的成员名>  非终结符
%type  <ptr> program ExtDefList 
这表示非终结符 ExtDefList 属性值的类型对应联合中成员 ptr 的类型，在本实验中对应一个树结点的指针
*/
%type <ptr> program ExtDefList ExtDef Specifier ExtDecList FuncDec ArrayDec CompSt VarList VarDec ParamDec Stmt StmList DefList Def DecList Dec Exp Args

//%token定义终结符的语义值类型
/*%token <type_id> ID，表示识别出来一个标识符后，标识符的字符串串值保存在成员 type_id */
//用bison对该文件编译时,带参数-d,生成的exp.tab.h中给这些单词进行编码,可在lex.l中包含parser.tab.h使用这些单词种类码
%token <type_int> INT //指定INT的语义值是type_int,由词法分析得到的数值
%token <type_id> ID RELOP TYPE //指定ID,RELOP 的语义值是type_id,由词法分析得到的标识符字符串
%token <type_float> FLOAT //指定ID的语义值是type_id,由词法分析得到的标识符字符串
%token <type_char> CHAR
%token LP RP LC RC SEMI COMMA LB RB
%token PLUS MINUS STAR DIV ASSIGNOP AND OR NOT IF ELSE WHILE RETURN COMADD COMSUB FOR//+=comadd，-=comsub，for，=assignop
%token EXT_DEF_LIST EXT_VAR_DEF FUNC_DEF FUNC_DEC EXT_DEC_LIST PARAM_LIST PARAM_DEC VAR_DEF DEC_LIST DEF_LIST COMP_STM STM_LIST EXP_STMT IF_THEN IF_THEN_ELSE FUNC_CALL ARGS FUNCTION PARAM ARG CALL LABEL GOTO JLT JLE JGT JGE EQ NEQ AUTOADD_L AUTOADD_R AUTOSUB_L AUTOSUB_R ARRAY_DEF ARRAY_DEC ARRAY
//优先级

%left COMADD COMSUB
%left ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right UMINUS NOT AUTOADD AUTOSUB
/*%nonassoc的含义是没有结合性,它一般与%prec结合使用表示该操作有同样的优先级*/
%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE


//规则部分
/*
Exp:  Exp ASSIGNOP Exp {$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno); } 
规则后面{}中的是当完成归约时要执行的语义动作。规则左部的 Exp 的属性值用$$表示，右部有 2 个 Exp，位置序号分别是 1 和 3，其属性值分别用$1 和$3表示
Stmt(statement) → error SEMI 表示对语句分析时，一旦有错，跳过分号（SEMI），继续进行语法分析
*/

%%
program: ExtDefList { display($1,0);Semantic_Analysis($1,0,0,' ',0);} /*归约到program，开始显示语法树,语义分析*/
         ;
/*ExtDefList：外部定义列表，即是整个语法树*/
ExtDefList: {$$=NULL;}/*整个语法树为空*/
            | ExtDef ExtDefList {$$=mknode(EXT_DEF_LIST,$1,$2,NULL,yylineno);}//每一个EXTDEFLIST的结点,其第1棵子树对应一个外部变量声明或函数
            ;
/*外部声明，声明外部变量或者声明函数*/
ExtDef: Specifier ExtDecList SEMI {$$=mknode(EXT_VAR_DEF,$1,$2,NULL,yylineno);}//该结点对应一个外部变量声明
        | Specifier ArrayDec SEMI {$$=mknode(ARRAY_DEF,$1,$2,NULL,yylineno);}//数组定义
        | Specifier FuncDec CompSt {$$=mknode(FUNC_DEF,$1,$2,$3,yylineno);}//该结点对应一个函数定义,类型+函数声明+复合语句
        | error SEMI {$$=NULL; printf("---缺少分号---\n");}
        ;
/*表示一个类型，int、float和char*/
Specifier: TYPE {$$=mknode(TYPE,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);$$->type=(!strcmp($1,"int")?INT:(!strcmp($1,"float")?FLOAT:CHAR));}
           ;
/*变量名称列表，由一个或多个变量组成，多个变量之间用逗号隔开*/
ExtDecList: VarDec {$$=$1;}/*每一个EXT_DECLIST的结点,其第一棵子树对应一个变量名(ID类型的结点),第二棵子树对应剩下的外部变量名*/
            | VarDec COMMA ExtDecList {$$=mknode(EXT_DEC_LIST,$1,$3,NULL,yylineno);}
            ;
/*变量名称，由一个ID组成*/
VarDec: ID {$$=mknode(ID,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//ID结点,标识符符号串存放结点的type_id
        ;
/*函数名+参数定义*/
FuncDec: ID LP VarList RP {$$=mknode(FUNC_DEC,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
         | ID LP RP {$$=mknode(FUNC_DEC,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
         | error RP {$$=NULL; printf("---函数左括号右括号不匹配---\n");}
         ;
/*数组声明*/
ArrayDec: ID LB Exp RB {$$=mknode(ARRAY_DEC,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
          | ID LB RB {$$=mknode(ARRAY_DEC,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
          | error RB {$$=NULL;printf("---数组定义错误---\n");}
/*参数定义列表，有一个到多个参数定义组成，用逗号隔开*/
VarList: ParamDec {$$=mknode(PARAM_LIST,$1,NULL,NULL,yylineno);}
         | ParamDec COMMA VarList {$$=mknode(PARAM_LIST,$1,$3,NULL,yylineno);}
         ;
/*参数定义，固定有一个类型和一个变量组成*/
ParamDec: Specifier VarDec {$$=mknode(PARAM_DEC,$1,$2,NULL,yylineno);}
          ;
/*复合语句，左右分别用大括号括起来，中间有定义列表和语句列表*/
CompSt: LC DefList StmList RC {$$=mknode(COMP_STM,$2,$3,NULL,yylineno);}
        | error RC {$$=NULL; printf("---复合语句内存在错误---\n");}
        ;
/*语句列表，由0个或多个语句stmt组成*/
StmList: {$$=NULL;}
         | Stmt StmList {$$=mknode(STM_LIST,$1,$2,NULL,yylineno);}
         ;
/*语句，可能为表达式，复合语句，return语句，if语句，if-else语句，while语句，for*/
Stmt: Exp SEMI {$$=mknode(EXP_STMT,$1,NULL,NULL,yylineno);}
      | CompSt {$$=$1;}//复合语句结点直接最为语句结点,不再生成新的结点
      | RETURN Exp SEMI {$$=mknode(RETURN,$2,NULL,NULL,yylineno);}
      | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE {$$=mknode(IF_THEN,$3,$5,NULL,yylineno);}
      | IF LP Exp RP Stmt ELSE Stmt {$$=mknode(IF_THEN_ELSE,$3,$5,$7,yylineno);}
      | WHILE LP Exp RP Stmt {$$=mknode(WHILE,$3,$5,NULL,yylineno);}
      | FOR LP Exp RP Stmt {$$=mknode(FOR,$3,$5,NULL,yylineno);}
      ;
/*定义列表，由0个或多个定义语句组成*/
DefList: {$$=NULL; }
         | Def DefList {$$=mknode(DEF_LIST,$1,$2,NULL,yylineno);}
         ;
/*定义一个或多个语句语句，由分号隔开*/
Def: Specifier DecList SEMI {$$=mknode(VAR_DEF,$1,$2,NULL,yylineno);}
     | Specifier ArrayDec SEMI {$$=mknode(ARRAY_DEF,$1,$2,NULL,yylineno);}
     ;
/*语句列表，由一个或多个语句组成，由逗号隔开，最终都成一个表达式*/
DecList: Dec {$$=mknode(DEC_LIST,$1,NULL,NULL,yylineno);}
         | Dec COMMA DecList {$$=mknode(DEC_LIST,$1,$3,NULL,yylineno);}
         ;
/*语句，一个变量名称或者一个赋值语句（变量名称等于一个表达式）*/
Dec: VarDec {$$=$1;}
     | VarDec ASSIGNOP Exp {$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno);strcpy($$->type_id,"ASSIGNOP");}
     ;
/*表达式*/
Exp: Exp ASSIGNOP Exp {$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno);strcpy($$->type_id,"ASSIGNOP");}//$$结点type_id空置未用,正好存放运算符
     | Exp AND Exp {$$=mknode(AND,$1,$3,NULL,yylineno);strcpy($$->type_id,"AND");}
     | Exp OR Exp {$$=mknode(OR,$1,$3,NULL,yylineno);strcpy($$->type_id,"OR");}
     | Exp RELOP Exp {$$=mknode(RELOP,$1,$3,NULL,yylineno);strcpy($$->type_id,$2);}//词法分析关系运算符号自身值保存在$2中
     | Exp PLUS Exp {$$=mknode(PLUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"PLUS");}
     | Exp MINUS Exp {$$=mknode(MINUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"MINUS");}
     | Exp STAR Exp {$$=mknode(STAR,$1,$3,NULL,yylineno);strcpy($$->type_id,"STAR");}
     | Exp DIV Exp {$$=mknode(DIV,$1,$3,NULL,yylineno);strcpy($$->type_id,"DIV");}
     | Exp COMADD Exp {$$=mknode(COMADD,$1,$3,NULL,yylineno);strcpy($$->type_id,"COMADD");}
     | Exp COMSUB Exp {$$=mknode(COMSUB,$1,$3,NULL,yylineno);strcpy($$->type_id,"COMSUB");}
     | LP Exp RP {$$=$2;}/*遇到左右括号，可直接忽略括号，Exp的值就为括号里面的Exp*/
     | MINUS Exp %prec UMINUS {$$=mknode(UMINUS,$2,NULL,NULL,yylineno);strcpy($$->type_id,"UMINUS");}
     | NOT Exp {$$=mknode(NOT,$2,NULL,NULL,yylineno);strcpy($$->type_id,"NOT");}
     | AUTOADD Exp {$$=mknode(AUTOADD_L,$2,NULL,NULL,yylineno);strcpy($$->type_id,"AUTOADD");}
     | AUTOSUB Exp {$$=mknode(AUTOSUB_L,$2,NULL,NULL,yylineno);strcpy($$->type_id,"AUTOSUB");}
     | Exp AUTOADD {$$=mknode(AUTOADD_R,$1,NULL,NULL,yylineno);strcpy($$->type_id,"AUTOADD");}
     | Exp AUTOSUB {$$=mknode(AUTOSUB_R,$1,NULL,NULL,yylineno);strcpy($$->type_id,"AUTOSUB");}
     | ID LP Args RP {$$=mknode(FUNC_CALL,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}/*函数定义后面的括号部分，只需要把括号里面的内容传入即可*/
     | ID LP RP {$$=mknode(FUNC_CALL,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}/*函数定义后面的括号部分没有参数*/
     | ID {$$=mknode(ID,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
     | INT {$$=mknode(INT,NULL,NULL,NULL,yylineno);$$->type_int=$1;$$->type=INT;}
     | FLOAT {$$=mknode(FLOAT,NULL,NULL,NULL,yylineno);$$->type_float=$1;$$->type=FLOAT;}
     | CHAR {$$=mknode(CHAR,NULL,NULL,NULL,yylineno); $$->type_char=$1;$$->type=CHAR;}
     ;
/*用逗号隔开的参数*/
Args: Exp COMMA Args {$$=mknode(ARGS,$1,$3,NULL,yylineno);}
      | Exp {$$=mknode(ARGS,$1,NULL,NULL,yylineno);}
      ;

//规则部分
%%
int main(int argc, char *argv[]){
  yyin=fopen(argv[1],"r");
  if (!yyin) 
    return 0;
  yylineno=1;
  yyparse();
  return 0;
}

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, ".\n");
}