%error-verbose
%locations
//声明部分,包含语法分析中需要的头文件包含，宏定义和全局变量的定义等
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
void display(struct ASTNode *,int);
%}

//辅助定义 用联合将这多种类型统一起来

%union {
	int    type_int;
	float  type_float;
	char   type_char[3];
	char   type_id[32];
	struct ASTNode *ptr;
};


//  %type 定义非终结符的语义值类型
%type  <ptr> program ExtDefList ExtDef  Specifier ExtDecList FuncDec CompSt VarList VarDec ParamDec Stmt StmList DefList Def DecList Dec Exp Args ArrayDec //INDEX FORDEC FOREXP1 FOREXP2 FOREXP3

//% token 定义终结符的语义值类型
%token <type_int> INT              /*指定INT的语义值是type_int，有词法分析得到的数值*/
%token <type_id> ID RELOP TYPE    /*指定ID,RELOP 的语义值是type_id，有词法分析得到的标识符字符串*/
%token <type_char> CHAR 
%token <type_float> FLOAT          /*指定ID的语义值是type_id，有词法分析得到的标识符字符串*/


%token LP RP LB RB LC RC SEMI COMMA      /*用bison对该文件编译时，带参数-d，生成的.tab.h中给这些单词进行编码，可在lex.l中包含parser.tab.h使用这些单词种类码*/
%token COMADD COMSUB COMSTAR COMDIV COMMOD PLUS MINUS STAR DIV MOD ASSIGNOP AND OR NOT IF ELSE WHILE RETURN FOR AUTOADD AUTOSUB //增加了+= -= *= /= %=
%token BREAK CONTINUE 

/*以下为接在上述token后依次编码的枚举常量，作为AST结点类型标记*/
/*%token EXT_DEF_LIST EXT_VAR_DEF FUNC_DEF FUNC_DEC EXT_DEC_LIST PARAM_LIST PARAM_DEC VAR_DEF DEC_LIST DEF_LIST COMP_STM STM_LIST EXP_STMT IF_THEN IF_THEN_ELSE
%token FUNC_CALL ARGS FUNCTION PARAM ARG CALL LABEL GOTO JLT JLE JGT JGE EQ NEQ ARRAY_DEC FOR_DEC CONTINUE_NODE BREAK_NODE BLANK ARRAY_DF FOR_EXP1 FOR_EXP2 FOR_EXP3 FOR_NODE ARRAY_CALL*/

//这里是优先级定义
%left COMADD COMSUB COMSTAR COMDIV COMMOD //+=这类复合运算优先级大于=
%left ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV MOD
%left AUTOADD AUTOSUB
%right UMINUS NOT 

%right 	LB
%left 	RB

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%%

//规则部分

program: ExtDefList    { display($1,0); semantic_Analysis0($1);}     //显示语法树,语义分析
         ; 
/*定义整个语法树*/
ExtDefList: {$$=NULL;}  //表示整个语法树为空
          | ExtDef ExtDefList {$$=mknode(2,EXT_DEF_LIST,yylineno,$1,$2);}   //每一个EXTDEFLIST的结点，其第1棵子树对应一个外部变量声明或函数
          ;  
/*外部声明，外部变量或函数*/
ExtDef:   Specifier ExtDecList SEMI   {$$=mknode(2,EXT_VAR_DEF,yylineno,$1,$2);}   //该结点对应一个外部变量声明
         |Specifier FuncDec CompSt    {$$=mknode(3,FUNC_DEF,yylineno,$1,$2,$3);}         //该结点对应一个函数定义
		// | Specifier ID ArrayDec {$$=mknode(2,ARRAY_DF,yylineno,$1,$2);}	//外部数组定义
         | error SEMI   {$$=NULL;printf("\t missing SEMI \t\n");}
         ;

/*表示一个类型,补充对char类型的定义*/
Specifier:  TYPE    {$$=mknode(0,TYPE,yylineno);strcpy($$->type_id,$1);$$->type=!strcmp($1,"int")?INT:(!strcmp($1,"float")?FLOAT:CHAR);}    
           ;      	

/*变量名称列表*/	   
ExtDecList:  VarDec      {$$=$1;}       /*每一个EXT_DECLIST的结点，其第一棵子树对应一个变量名(ID类型的结点),第二棵子树对应剩下的外部变量名*/
           | VarDec COMMA ExtDecList {$$=mknode(2,EXT_DEC_LIST,yylineno,$1,$3);}
           ;  
		   
/*变量名称，由一个ID组成*/
VarDec:  ID          {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}   //ID结点，标识符符号串存放结点的type_id
		| ID ArrayDec {$$=mknode(1,ARRAY_DF,yylineno,$2);strcpy($$->type_id,$1);}   //数组
		;

//补充数组声明
ArrayDec: LB Exp RB {$$ = $2;/*$$=mknode(1,ARRAY_DEC,yylineno,$2);strcpy($$->type_id,"ARRAY_DEC");*/}
          | LB Exp RB ArrayDec {$$=mknode(2,ARRAY_DEC,yylineno,$2,$4);strcpy($$->type_id,"ARRAY_DEC");}
		  | error RB {$$=NULL;printf("\t define array error \t\n");}
		  ;

/*INDEX: INT {$$=mknode(0,INT,yylineno);$$->type_int=$1;$$->type=INT;}*/
		  ;

/*函数定义*/
FuncDec: ID LP VarList RP   {$$=mknode(1,FUNC_DEC,yylineno,$3);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
		|ID LP  RP   {$$=mknode(0,FUNC_DEC,yylineno);strcpy($$->type_id,$1);$$->ptr[0]=NULL;}//函数名存放在$$->type_id
		//| error RP {$$=NULL; printf("\t define function error\n");}
		;
		
//这里是参数列表
VarList: ParamDec  {$$=mknode(1,PARAM_LIST,yylineno,$1);}
        | ParamDec COMMA  VarList  {$$=mknode(2,PARAM_LIST,yylineno,$1,$3);}
        ;
		
//参数定义
ParamDec: Specifier VarDec         {$$=mknode(2,PARAM_DEC,yylineno,$1,$2);}
         ;

//复合语句
CompSt: LC DefList StmList RC    {$$=mknode(2,COMP_STM,yylineno,$2,$3);}
		//| error RC {$$=NULL; printf("\t compst error\n");}
       ;
	   
/*语句列表，由0个或多个语句stmt组成*/	 
StmList: {$$=NULL; }  
        | Stmt StmList  {$$=mknode(2,STM_LIST,yylineno,$1,$2);}
        ;
		
//语句
Stmt:   Exp SEMI    {$$=mknode(1,EXP_STMT,yylineno,$1);}
      | CompSt      {$$=$1;}      //复合语句结点直接最为语句结点，不再生成新的结点
      | RETURN Exp SEMI   {$$=mknode(1,RETURN,yylineno,$2);}
      | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE   {$$=mknode(2,IF_THEN,yylineno,$3,$5);}
      | IF LP Exp RP Stmt ELSE Stmt   {$$=mknode(3,IF_THEN_ELSE,yylineno,$3,$5,$7);}
      | WHILE LP Exp RP Stmt {$$=mknode(2,WHILE,yylineno,$3,$5);}
      | FOR LP Exp SEMI Exp SEMI Exp RP Stmt {$$=mknode(4,FOR_NODE,yylineno,$3,$5,$7,$9);}
      | BREAK SEMI		 {$$=mknode(0,BREAK_NODE,yylineno);strcpy($$->type_id,"BREAK");}
      | CONTINUE SEMI   {$$=mknode(0,CONTINUE_NODE,yylineno);strcpy($$->type_id,"CONTINUE");}
      | SEMI {$$ = mknode(0,BLANK,yylineno);strcpy($$->type_id,"BLANK");}  //空语句
      ;
	 
/*枚举for循环里的条件*/
// FORDEC: FOREXP1 SEMI FOREXP2 SEMI FOREXP3 {$$=mknode(3, FOR_DEC,yylineno,$1,$3,$5);}
//        | FOREXP1 SEMI SEMI FOREXP3 {$$=mknode(3, FOR_DEC,yylineno,$1,NULL,$4);}
//        | FOREXP1 SEMI FOREXP2 SEMI {$$=mknode(3, FOR_DEC,yylineno,$1,$3,NULL);}
//        | FOREXP1 SEMI SEMI {$$=mknode(3, FOR_DEC,yylineno,$1,NULL,NULL);}
//        | SEMI FOREXP2 SEMI FOREXP3 {$$=mknode(3, FOR_DEC,yylineno,NULL,$2,$4);}
//        | SEMI FOREXP2 SEMI  {$$=mknode(3, FOR_DEC,yylineno,NULL,$2,NULL);}
//        | SEMI SEMI FOREXP3 {$$=mknode(3, FOR_DEC,yylineno,NULL,NULL,$3);}     
//        | SEMI SEMI {$$=mknode(3, FOR_DEC, yylineno, NULL, NULL, NULL);}  
//        ;

// FOREXP1:  DecList {$$=mknode(1, FOR_EXP1, yylineno, $1);}
//         | Specifier DecList {$$=mknode(2, FOR_EXP1, yylineno, $1, $2);}
//         ;
// FOREXP2:  Exp COMMA FOREXP2 {$$=mknode(2, FOR_EXP2, yylineno, $1,$3);}
// 		| Exp {$$=mknode(1, FOR_EXP2, yylineno, $1);}
//         ;
// FOREXP3:  Exp COMMA FOREXP3 {$$=mknode(2, FOR_EXP3, yylineno, $1,$3);}
//         | Exp {$$=mknode(2, FOR_EXP3, yylineno, $1, NULL);}
//         ;
// 		;
	
/*定义列表*/
DefList: {$$=NULL; }
        | Def DefList {$$=mknode(2,DEF_LIST,yylineno,$1,$2);}
        | error SEMI   {$$=NULL;}
        ;
		
/*定义*/
Def:    Specifier DecList SEMI {$$=mknode(2,VAR_DEF,yylineno,$1,$2);}
		//| Specifier ID ArrayDec SEMI {$$=mknode(2,ARRAY_DF,yylineno,$1,$2);}
        ;

DecList: Dec  {$$=mknode(1,DEC_LIST,yylineno,$1);}
       | Dec COMMA DecList  {$$=mknode(2,DEC_LIST,yylineno,$1,$3);}
	   ;
Dec:     VarDec  {$$=$1;}
       | VarDec ASSIGNOP Exp  {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}
       ;
	   
//表达式
Exp:    Exp ASSIGNOP Exp {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}//$$结点type_id空置未用，正好存放运算符
      | Exp AND Exp   {$$=mknode(2,AND,yylineno,$1,$3);strcpy($$->type_id,"AND");}
      | Exp OR Exp    {$$=mknode(2,OR,yylineno,$1,$3);strcpy($$->type_id,"OR");}
      | Exp RELOP Exp {$$=mknode(2,RELOP,yylineno,$1,$3);strcpy($$->type_id,$2);}  //词法分析关系运算符号自身值保存在$2中
      | Exp PLUS Exp  {$$=mknode(2,PLUS,yylineno,$1,$3);strcpy($$->type_id,"PLUS");}
      | Exp MINUS Exp {$$=mknode(2,MINUS,yylineno,$1,$3);strcpy($$->type_id,"MINUS");}
      | Exp STAR Exp  {$$=mknode(2,STAR,yylineno,$1,$3);strcpy($$->type_id,"STAR");}
      | Exp DIV Exp   {$$=mknode(2,DIV,yylineno,$1,$3);strcpy($$->type_id,"DIV");}
	  | Exp MOD Exp   {$$=mknode(2,MOD,yylineno,$1,$3);strcpy($$->type_id,"MOD");}
	  | Exp COMADD Exp {$$=mknode(2,COMADD,yylineno,$1,$3);strcpy($$->type_id,"COMADD");}
      | Exp COMSUB Exp {$$=mknode(2,COMSUB,yylineno,$1,$3);strcpy($$->type_id,"COMSUB");}
      | Exp COMSTAR Exp {$$=mknode(2,COMSTAR,yylineno,$1,$3);strcpy($$->type_id,"COMSTAR");}
      | Exp COMDIV Exp {$$=mknode(2,COMDIV,yylineno,$1,$3);strcpy($$->type_id,"COMDIV");}
      | Exp COMMOD Exp {$$=mknode(2,COMMOD,yylineno,$1,$3);strcpy($$->type_id,"COMMOD");}	  
      | LP Exp RP     {$$=$2;}
      | MINUS Exp %prec UMINUS   {$$=mknode(1,UMINUS,yylineno,$2);strcpy($$->type_id,"UMINUS");}
      | NOT Exp       {$$=mknode(1,NOT,yylineno,$2);strcpy($$->type_id,"NOT");}
      | AUTOADD  Exp      {$$=mknode(1,AUTOADD,yylineno,$2);strcpy($$->type_id,"AUTOADD");}
      | Exp AUTOADD      {$$=mknode(1,AUTOADD,yylineno,$1);strcpy($$->type_id,"AUTOADD");}
	  | AUTOSUB  Exp      {$$=mknode(1,AUTOSUB,yylineno,$2);strcpy($$->type_id,"AUTOSUB");}
      | Exp AUTOSUB      {$$=mknode(1,AUTOSUB,yylineno,$1);strcpy($$->type_id,"AUTOSUB");}
	 // | LB Args RB   {$$=$2;} 
	  //| ID ArrayDec  {$$=mknode(1,ID,yylineno,$3);strcpy($$->type_id,$1);} 
	  
      | ID LP Args RP {$$=mknode(1,FUNC_CALL,yylineno,$3);strcpy($$->type_id,$1);}  //带括号应该是函数括号内的参数内容
      | ID LP RP      {$$=mknode(0,FUNC_CALL,yylineno);strcpy($$->type_id,$1);}
	  | ID ArrayDec {$$=mknode(1,ARRAY_CALL,yylineno,$2);strcpy($$->type_id,$1);}
      | ID            {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}
      | INT           {$$=mknode(0,INT,yylineno);$$->type_int=$1;$$->type=INT;}
      | FLOAT         {$$=mknode(0,FLOAT,yylineno);$$->type_float=$1;$$->type=FLOAT;}
	  | CHAR 		  {$$=mknode(0,CHAR,yylineno); strcpy($$->type_char,$1);$$->type=CHAR;}
       //   | SEMI {$$ = mknode(0,BLANK,yylineno);strcpy($$->type_id,"BLANK");}  //空语句
      ;
Args:    Exp COMMA Args    {$$=mknode(2,ARGS,yylineno,$1,$3);}
       | Exp               {$$=mknode(1,ARGS,yylineno,$1);}
       ;
       
%%

int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return -1;
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
 
