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
        void display(struct ASTNode *,int);
        void displayRoot();
%} 


//辅助定义部分
%union {
	int    type_int;
        char   type_char;
	float  type_float;
	char   type_id[32];
	struct ASTNode *ptr;
};

//  %type 定义非终结符的语义值类型
%type <ptr> program ExtDefList ExtDef  Specifier ExtDecList FuncDec CompSt VarList VarDec ParamDec Stmt StmList DefList Def DecList Dec Exp Args 
%type <ptr> CaseStmtList CaseStmt DefaultStmt Struct_dec StructName
%type <ptr> ForDec ForExp1 ForExp2 ForExp3
%type <ptr> Arraylist
/*加入了ArryList*/

//% token 定义终结符的语义值类型
%token <type_char> CHAR
%token <type_int> INT              /*指定INT的语义值是type_int，有词法分析得到的数值*/
%token <type_id> ID ERRORID STRING RELOP TYPE    /*指定ID,RELOP,TYPE,STRING 的语义值是type_id，有词法分析得到的标识符字符串*/
%token <type_float> FLOAT          /*指定FLOAT的语义值是type_float，有词法分析得到的标识符字符串*/
%token STRUCT RETURN FOR SWITCH CASE COLON DEFAULT
%token STRUCT_VISIT STRUCT_NEW STRUCT_DEC EXT_STRUCT_DEC/*结构体*/
%token CASE_STMT CASE_STMT_LIST DEFAULT_STMT
%token FOR_DEC FOR_EXP1 FOR_EXP2 FOR_EXP3

%token DPLUS LP RP LC RC LB RB SEMI COMMA DOT      /*用bison对该文件编译时，带参数-d，生成的.tab.h中给这些单词进行编码，可在lex.l中包含parser.tab.h使用这些单词种类码*/
%token PLUS MINUS STAR DIV MOD ASSIGNOP PLUSASSIGNOP MINUSASSIGNOP STARASSIGNOP DIVASSIGNOP MODASSIGNOP AND OR NOT AUTOPLUS AUTOMINUS IF ELSE WHILE BREAK CONTINUE 
/*以下为接在上述token后依次编码的枚举常量，作为AST结点类型标记*/
%token EXT_DEF_LIST EXT_VAR_DEF FUNC_DEF FUNC_DEC EXT_DEC_LIST PARAM_LIST PARAM_DEC VAR_DEF DEC_LIST DEF_LIST COMP_STM STM_LIST EXP_STMT IF_THEN IF_THEN_ELSE
%token FUNC_CALL ARGS FUNCTION PARAM ARG CALL LABEL GOTO JLT JLE JGT JGE EQ NEQ
%token ARRAY_LIST //加入Array
//优先级
%left ASSIGNOP PLUSASSIGNOP MINUSASSIGNOP STARASSIGNOP DIVASSIGNOP MODASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV MOD
%left AUTOPLUS AUTOMINUS
%right UMINUS NOT DPLUS DMINUS
%left LB RB LP RP DOT

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

//规则定义部分
%%
program: ExtDefList    {displayRoot();display($1,0);}     //显示语法树,语义分析
         ; 
ExtDefList: {$$=NULL;}
          | ExtDef ExtDefList {$$=mknode(2,EXT_DEF_LIST,yylineno,$1,$2);}   //每一个EXTDEFLIST的结点，其第1棵子树对应一个外部变量声明或函数
          ;  
ExtDef:   Specifier ExtDecList SEMI   {$$=mknode(2,EXT_VAR_DEF,yylineno,$1,$2);}   //该结点对应一个外部变量声明
         |Specifier FuncDec CompSt    {$$=mknode(3,FUNC_DEF,yylineno,$1,$2,$3);}         //该结点对应一个函数定义
         |Struct_dec SEMI{$$=mknode(1, EXT_STRUCT_DEC, yylineno,$1);}
         | error SEMI   {$$=NULL;}
         ;
Specifier:  TYPE    {$$=mknode(0,TYPE,yylineno);strcpy($$->type_id,$1);$$->type=!strcmp($1,"int")?INT:FLOAT;}   
           ;      
ExtDecList:  VarDec      {$$=$1;}       /*每一个EXT_DECLIST的结点，其第一棵子树对应一个变量名(ID类型的结点),第二棵子树对应剩下的外部变量名*/
           | VarDec COMMA ExtDecList {$$=mknode(2,EXT_DEC_LIST,yylineno,$1,$3);}
           ;  
VarDec:  ID          {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);} |   //ID结点，标识符符号串存放结点的type_id
         ID Arraylist  {$$=mknode(1,ARRAY_LIST,yylineno,$2);strcpy($$->type_id,$1);} 
         ;

Arraylist:  LB INT RB           {$$=mknode(0,ARRAY_LIST,yylineno);$$->type_int=$2;}
            | LB INT RB Arraylist       {$$=mknode(2,ARRAY_LIST,yylineno,$2,$4);$$->type_int=$2}
        ;
FuncDec: ID LP VarList RP   {$$=mknode(1,FUNC_DEC,yylineno,$3);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
	|ID LP  RP   {$$=mknode(0,FUNC_DEC,yylineno);strcpy($$->type_id,$1);$$->ptr[0]=NULL;}//函数名存放在$$->type_id
        ;  
VarList: ParamDec  {$$=mknode(1,PARAM_LIST,yylineno,$1);}
        | ParamDec COMMA  VarList  {$$=mknode(2,PARAM_LIST,yylineno,$1,$3);}
        ;
ParamDec: Specifier VarDec         {$$=mknode(2,PARAM_DEC,yylineno,$1,$2);}
         ;

CompSt: LC DefList StmList RC    {$$=mknode(2,COMP_STM,yylineno,$2,$3);}
       ;
StmList: {$$=NULL; }  
        | Stmt StmList  {$$=mknode(2,STM_LIST,yylineno,$1,$2);}
        ;
Stmt:   Exp SEMI    {$$=mknode(1,EXP_STMT,yylineno,$1);}
      | CompSt      {$$=$1;}      //复合语句结点直接最为语句结点，不再生成新的结点
      | RETURN Exp SEMI   {$$=mknode(1,RETURN,yylineno,$2);}
      | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE   {$$=mknode(2,IF_THEN,yylineno,$3,$5);}
      | IF LP Exp RP Stmt ELSE Stmt   {$$=mknode(3,IF_THEN_ELSE,yylineno,$3,$5,$7);}
      | WHILE LP Exp RP Stmt {$$=mknode(2,WHILE,yylineno,$3,$5);}
      | CONTINUE SEMI	{ $$ = mknode(0, CONTINUE, yylineno); strcpy($$->type_id, "CONTINUE"); }
      | BREAK	SEMI	{ $$ = mknode(0, BREAK, yylineno); strcpy($$->type_id, "BREAK"); }
      | FOR LP ForDec RP Stmt {$$=mknode(2,FOR,yylineno,$3,$5);} //FOR循环识别 for(FORDEC):Stmt
      | SWITCH LP Exp RP LC CaseStmtList RC {$$=mknode(2, SWITCH, yylineno, $3, $6);} //SWITCH识别
      ;
//用于识别Default:*****
DefaultStmt: DEFAULT COLON StmList {$$=mknode(1, DEFAULT_STMT, yylineno, $3);}
        ;

//Case(INT): Case(CHAR):的识别
CaseStmt: CASE INT COLON StmList {$$=mknode(1, CASE_STMT, yylineno, $4);$$->type_int=$2;$$->type=INT;}
        | CASE CHAR COLON StmList {$$=mknode(1, CASE_STMT, yylineno, $4);$$->type_char=$2;$$->type=CHAR;}
        ;

//用于识别连续多个case+Default(DEFAULT为终结符)
CaseStmtList: 
          {$$=NULL;}
        | CaseStmt CaseStmtList {$$=mknode(2, CASE_STMT_LIST, yylineno, $1, $2);}
        | DefaultStmt {$$=mknode(1, CASE_STMT_LIST, yylineno,$1);}
        ;

//用于识别For循环
//for(int i ; i < 10 ;i++)
//for(int i;i<10;)
//for(int i;;i++)
//for(int i;;)
//for(;i<10;i++)
//for(;i<10;)
//for(;;i++)
//for(;;)死循环
ForDec: ForExp1 SEMI ForExp2 SEMI ForExp3 {$$=mknode(3, FOR_DEC,yylineno,$1,$3,$5);}
       | ForExp1 SEMI SEMI ForExp3 {$$=mknode(3, FOR_DEC,yylineno,$1,NULL,$4);}
       | ForExp1 SEMI ForExp2 SEMI {$$=mknode(3, FOR_DEC,yylineno,$1,$3,NULL);}
       | ForExp1 SEMI SEMI {$$=mknode(3, FOR_DEC,yylineno,$1,NULL,NULL);}
       | SEMI ForExp2 SEMI ForExp3 {$$=mknode(3, FOR_DEC,yylineno,NULL,$2,$4);}
       | SEMI ForExp2 SEMI  {$$=mknode(3, FOR_DEC,yylineno,NULL,$2,NULL);}
       | SEMI SEMI ForExp3 {$$=mknode(3, FOR_DEC,yylineno,NULL,NULL,$3);}     
       | SEMI SEMI {$$=mknode(3, FOR_DEC, yylineno, NULL, NULL, NULL);}  
       ;

ForExp1:  DecList {$$=mknode(1, FOR_EXP1, yylineno, $1);}
        | Specifier DecList {$$=mknode(2, FOR_EXP1, yylineno, $1, $2);}
        ;
ForExp2: Exp {$$=mknode(1, FOR_EXP2, yylineno, $1);}
        ;
ForExp3:  Exp COMMA ForExp3 {$$=mknode(2, FOR_EXP3, yylineno, $1,$3);}
        | Exp {$$=mknode(2, FOR_EXP3, yylineno, $1, NULL);}
        ;

//struct name {DefList}识别
//struct name ID识别
Struct_dec: STRUCT StructName LC DefList RC {$$=mknode(2, STRUCT_NEW, yylineno, $2, $4);}
        | STRUCT ID ID {$$=mknode(0,STRUCT_DEC,yylineno);strcpy($$->type_id,$3);}
        ;
StructName: {$$=NULL;}
        | ID {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}
        ;

DefList: {$$=NULL; }
        | Def DefList {$$=mknode(2,DEF_LIST,yylineno,$1,$2);}
        | error SEMI   {$$=NULL;}
        ;
Def:    Specifier DecList SEMI {$$=mknode(2,VAR_DEF,yylineno,$1,$2);}
        |Struct_dec SEMI {$$=$1}
        ;
DecList: Dec  {$$=mknode(1,DEC_LIST,yylineno,$1);}
       | Dec COMMA DecList  {$$=mknode(2,DEC_LIST,yylineno,$1,$3);}
	   ;
Dec:     VarDec  {$$=$1;}
       | VarDec ASSIGNOP Exp  {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}
       ;
Exp:    Exp ASSIGNOP Exp {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}//$$结点type_id空置未用，正好存放运算符
      | Exp PLUSASSIGNOP Exp {$$=mknode(2,PLUSASSIGNOP,yylineno,$1,$3);strcpy($$->type_id, "PLUSASSIGNOP");}
      | Exp MINUSASSIGNOP Exp {$$=mknode(2,MINUSASSIGNOP,yylineno,$1,$3);strcpy($$->type_id, "MINUSASSIGNOP");}
      | Exp STARASSIGNOP Exp {$$=mknode(2, STARASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"STARASSIGNOP");}
      | Exp DIVASSIGNOP Exp {$$=mknode(2,DIVASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"DIVASSIGNOP");}
      | Exp MODASSIGNOP Exp {$$=mknode(2,MODASSIGNOP,yylineno,$1,$3);strcpy($$->type_id, "MODASSIGNOP");}
      | Exp AND Exp   {$$=mknode(2,AND,yylineno,$1,$3);strcpy($$->type_id,"AND");}
      | Exp OR Exp    {$$=mknode(2,OR,yylineno,$1,$3);strcpy($$->type_id,"OR");}
      | Exp RELOP Exp {$$=mknode(2,RELOP,yylineno,$1,$3);strcpy($$->type_id,$2);}  //词法分析关系运算符号自身值保存在$2中
      | Exp PLUS Exp  {$$=mknode(2,PLUS,yylineno,$1,$3);strcpy($$->type_id,"PLUS");}
      | Exp MINUS Exp {$$=mknode(2,MINUS,yylineno,$1,$3);strcpy($$->type_id,"MINUS");}
      | Exp STAR Exp  {$$=mknode(2,STAR,yylineno,$1,$3);strcpy($$->type_id,"STAR");}
      | Exp DIV Exp   {$$=mknode(2,DIV,yylineno,$1,$3);strcpy($$->type_id,"DIV");}
      | Exp MOD Exp   {$$=mknode(2,MOD,yylineno,$1,$3);strcpy($$->type_id,"MOD");}
      | Exp AUTOPLUS  {$$=mknode(1,AUTOPLUS,yylineno,$1);strcpy($$->type_id, "RPAUTOPLUS");}
      | Exp AUTOMINUS {$$=mknode(1,AUTOMINUS,yylineno,$1);strcpy($$->type_id,"RPAUTOMINUS");}
      | AUTOPLUS Exp  {$$=mknode(1,AUTOPLUS,yylineno,$2);strcpy($$->type_id, "LPAUTOPLUS");}
      | AUTOMINUS Exp {$$=mknode(1,AUTOMINUS,yylineno,$2);strcpy($$->type_id, "LPAUTOMINUS");}
      | LP Exp RP     {$$=$2;}
      | MINUS Exp %prec UMINUS   {$$=mknode(1,UMINUS,yylineno,$2);strcpy($$->type_id,"UMINUS");}
      | NOT Exp       {$$=mknode(1,NOT,yylineno,$2);strcpy($$->type_id,"NOT");}
      | DPLUS Exp      {$$=mknode(1,DPLUS,yylineno,$2);strcpy($$->type_id,"DPLUS");}
      | Exp DPLUS      {$$=mknode(1,DPLUS,yylineno,$1);strcpy($$->type_id,"DPLUS");}
      | ID LP Args RP {$$=mknode(1,FUNC_CALL,yylineno,$3);strcpy($$->type_id,$1);}
      | ID LP RP      {$$=mknode(0,FUNC_CALL,yylineno);strcpy($$->type_id,$1);}
      | ID            {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}
      | INT           {$$=mknode(0,INT,yylineno);$$->type_int=$1;$$->type=INT;}
      | CHAR          {$$=mknode(0,CHAR,yylineno);$$->type_char=$1;$$->type=CHAR;}
      | STRING        {$$=mknode(0,STRING,yylineno);strcpy($$->type_id,$1);$$->type=STRING;}
      | FLOAT         {$$=mknode(0,FLOAT,yylineno);$$->type_float=$1;$$->type=FLOAT;}
      | LB Args RB    {$$=$2;} //数组
      | ID Arraylist  {$$=mknode(1,ID,yylineno,$2);strcpy($$->type_id,$1);} 
      | Exp DOT ID {$$=mknode(1, STRUCT_VISIT, yylineno, $1);strcpy($$->type_id,$3);} //访问结构体元素   
      ;
Args:    Exp COMMA Args    {$$=mknode(2,ARGS,yylineno,$1,$3);}
       | Exp               {$$=mknode(1,ARGS,yylineno,$1);}
       ;
%%

int main(int argc, char *argv[]){
        yyin=fopen(argv[1],"r");
	if (!yyin) 
        return 0;
	yylineno=1;
	yyparse();
	return 0;
}

void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}