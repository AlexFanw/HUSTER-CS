#include "def.h"
#define SHOW 0

struct ASTNode* mknode(int num, int kind, int pos, ...) {
	struct ASTNode* T = (struct ASTNode*)calloc(sizeof(struct ASTNode), 1);
	int i = 0;
	T->kind = kind;
	T->pos = pos;
	va_list pArgs;
	va_start(pArgs, pos);
	for (i = 0; i < num; i++)
		T->ptr[i] = va_arg(pArgs, struct ASTNode*);
	while (i < 4) T->ptr[i++] = NULL;
	va_end(pArgs);
	return T;
}


void display(struct ASTNode* T, int indent)
{//对抽象语法树的先根遍历
#if SHOW

	int i = 1;
	struct ASTNode* T0;
	if (T)
	{
		switch (T->kind) {
		case EXT_DEF_LIST:
			display(T->ptr[0], indent);    //显示该外部定义（外部变量和函数）列表中的第一个
			display(T->ptr[1], indent);    //显示该外部定义列表中的其它外部定义
			break;
		case EXT_VAR_DEF:
			printf("%*c外部变量定义：(%d)\n", indent, ' ', T->pos);
			display(T->ptr[0], indent + 3);        //显示外部变量类型
			printf("%*c变量名：\n", indent + 3, ' ');
			display(T->ptr[1], indent + 6);        //显示变量列表
			break;
		case TYPE:
			printf("%*c类型： %s\n", indent, ' ', T->type_id);
			break;
		case EXT_DEC_LIST:
			display(T->ptr[0], indent);     //依次显示外部变量名，
			display(T->ptr[1], indent);     //后续还有相同的，仅显示语法树此处理代码可以和类似代码合并
			break;
		case FUNC_DEF:
			printf("%*c函数定义：(%d)\n", indent, ' ', T->pos);
			display(T->ptr[0], indent + 3);      //显示函数返回类型
			display(T->ptr[1], indent + 3);      //显示函数名和参数
			display(T->ptr[2], indent + 3);      //显示函数体
			break;
		case FUNC_DEC:
			printf("%*c函数名：%s\n", indent, ' ', T->type_id);
			if (T->ptr[0]) {
				printf("%*c函数形参：\n", indent, ' ');
				display(T->ptr[0], indent + 3);  //显示函数参数列表
			}
			else printf("%*c无参函数\n", indent + 3, ' ');
			break;
		case ARRAY_DF:
			printf("%*c 数组 %s", indent, ' ', T->type_id);
			display(T->ptr[0], indent + 3);
			printf("\n");
			break;
		case ARRAY_DEC:
			if (T->ptr[0])
				printf("[%d]", T->ptr[0]->type_int);
			display(T->ptr[1], 0);
			break;
		case PARAM_LIST:
			display(T->ptr[0], indent);     //依次显示全部参数类型和名称，
			display(T->ptr[1], indent);
			break;
		case PARAM_DEC:
			printf("%*c类型：%s, 参数名：%s\n", indent, ' ', T->ptr[0]->type_id, T->ptr[1]->type_id);
			break;
		case EXP_STMT:
			printf("%*c表达式语句：(%d)\n", indent, ' ', T->pos);
			display(T->ptr[0], indent + 3);
			break;
		case RETURN:
			printf("%*c返回语句：(%d)\n", indent, ' ', T->pos);
			display(T->ptr[0], indent + 3);
			break;
		case COMP_STM:
			printf("%*c复合语句：(%d)\n", indent, ' ', T->pos);
			printf("%*c复合语句的变量定义部分：\n", indent + 3, ' ');
			display(T->ptr[0], indent + 6);      //显示定义部分
			printf("%*c复合语句的语句部分：\n", indent + 3, ' ');
			display(T->ptr[1], indent + 6);      //显示语句部分
			break;
		case STM_LIST:
			display(T->ptr[0], indent);      //显示第一条语句
			display(T->ptr[1], indent);        //显示剩下语句
			break;
		case FOR_NODE:
			printf("%*cFOR循环语句：\n", indent, ' ');
			display(T->ptr[0], indent + 3); //显示循环条件
			printf("%*c循环体：\n", indent + 3, ' ');
			display(T->ptr[1], indent + 6); //显示循环体
			break;
		case FOR_DEC:
			//printf("%*c循环初始定义：\n", indent + 3, ' ');
			display(T->ptr[0], indent + 6);
			//printf("%*c循环条件：\n", indent + 3, ' ');
			display(T->ptr[1], indent + 6);
			//printf("%*c循环变换表达式：\n", indent + 3, ' ');
			display(T->ptr[2], indent + 6);
			break;
		case FOR_EXP1:
			printf("%*cFOR循环初始语句\n", indent, ' ');
			display(T->ptr[0], indent + 3);
			display(T->ptr[1], indent + 3);
			break;
		case FOR_EXP2:
			printf("%*cFOR循环条件语句\n", indent, ' ');
			T0 = T;
			while (T0)
			{
				display(T0->ptr[0], indent + 3);
				T0 = T0->ptr[1];
			}
			display(T->ptr[0], indent + 3);
			break;
		case FOR_EXP3:
			printf("%*cFOR循环结束条件\n", indent, ' ');
			T0 = T;
			while (T0)
			{
				display(T0->ptr[0], indent + 3);
				T0 = T0->ptr[1];
			}
			break;
		case BREAK_NODE:
			printf("%*cBreak语句\n", indent, ' ');
			break;
		case BLANK:
			//printf("%*c空语句\n", indent, ' ');
			break;
		case CONTINUE_NODE:
			printf("%*cContinue语句\n", indent, ' ');
			break;
		case WHILE:         printf("%*c循环语句：(%d)\n", indent, ' ', T->pos);
			printf("%*c循环条件：\n", indent + 3, ' ');
			display(T->ptr[0], indent + 6);      //显示循环条件
			printf("%*c循环体：(%d)\n", indent + 3, ' ', T->pos);
			display(T->ptr[1], indent + 6);      //显示循环体
			break;
		case IF_THEN:       printf("%*c条件语句(IF_THEN)：(%d)\n", indent, ' ', T->pos);
			printf("%*c条件：\n", indent + 3, ' ');
			display(T->ptr[0], indent + 6);      //显示条件
			printf("%*cIF子句：(%d)\n", indent + 3, ' ', T->pos);
			display(T->ptr[1], indent + 6);      //显示if子句
			break;
		case IF_THEN_ELSE:  printf("%*c条件语句(IF_THEN_ELSE)：(%d)\n", indent, ' ', T->pos);
			printf("%*c条件：\n", indent + 3, ' ');
			display(T->ptr[0], indent + 6);      //显示条件
			printf("%*cIF子句：(%d)\n", indent + 3, ' ', T->pos);
			display(T->ptr[1], indent + 6);      //显示if子句
			printf("%*cELSE子句：(%d)\n", indent + 3, ' ', T->pos);
			display(T->ptr[2], indent + 6);      //显示else子句
			break;
		case DEF_LIST:
			display(T->ptr[0], indent);    //显示该局部变量定义列表中的第一个
			display(T->ptr[1], indent);    //显示其它局部变量定义
			break;
		case VAR_DEF:
			printf("%*c局部变量定义：(%d)\n", indent, ' ', T->pos);
			display(T->ptr[0], indent + 3);   //显示变量类型
			display(T->ptr[1], indent + 3);   //显示该定义的全部变量名
			break;
		case DEC_LIST:
			printf("%*c变量名：\n", indent, ' ');
			T0 = T;
			while (T0) {
				if (T0->ptr[0]->kind == ID)
					printf("%*c %s\n", indent + 6, ' ', T0->ptr[0]->type_id);
				else if (T0->ptr[0]->kind == ASSIGNOP)
				{
					if (T0->ptr[0]->ptr[0]->kind == ARRAY_DF)
						display(T0->ptr[0]->ptr[0], indent);
					//var_dec assignop exp的情况
					printf("%*c %s ASSIGNOP\n ", indent + 6, ' ', T0->ptr[0]->ptr[0]->type_id);
					display(T0->ptr[0]->ptr[1], indent + strlen(T0->ptr[0]->ptr[0]->type_id) + 7);        //显示初始化表达式
				}
				else if (T0->ptr[0]->kind == ARRAY_DF) {
					printf("%*c 数组 %s\n", indent + 6, ' ', T0->ptr[0]->type_id);
					display(T0->ptr[0], indent);
				}
				T0 = T0->ptr[1];
			}
			break;
		case ARRAY_CALL:
			display(T->ptr[0], indent);
			printf("%*c数组下标：\n", indent, ' ');
			display(T->ptr[1], indent);
			break;
		case ID:
			printf("%*cID： %s\n", indent, ' ', T->type_id);
			break;
		case INT:
			printf("%*cINT：%d\n", indent, ' ', T->type_int);
			break;
		case FLOAT:
			printf("%*cFLAOT：%f\n", indent, ' ', T->type_float);
			break;
		case CHAR:
			printf("%*cCHAR: %s\n", indent, ' ', T->type_char);
			break;
		case ASSIGNOP:
			T0 = T;
			if (T0->ptr[0]->kind == ARRAY_DF) {
				printf("%*c 数组 %s", indent, ' ', T->type_id);
				display(T0->ptr[0]->ptr[0], indent + 3);
				printf("\n");
			}
		case AND:
		case OR:
		case RELOP:
		case PLUS:
		case MINUS:
		case STAR:
		case DIV:
		case COMADD:
		case COMSUB:
		case COMSTAR:
		case COMDIV:
		case COMMOD:
			printf("%*c%s\n", indent, ' ', T->type_id);
			display(T->ptr[0], indent + 3);
			display(T->ptr[1], indent + 3);
			break;
		case AUTOADD:
		case AUTOSUB:
			printf("%*c%s\n", indent, ' ', T->type_id);
			display(T->ptr[0], indent + 3);
			display(T->ptr[1], indent + 3);
			break;
		case NOT:
		case UMINUS:
			printf("%*c%s\n", indent, ' ', T->type_id);
			display(T->ptr[0], indent + 3);
			break;
		case FUNC_CALL:
			printf("%*c函数调用：(%d)\n", indent, ' ', T->pos);
			printf("%*c函数名：%s\n", indent + 3, ' ', T->type_id);
			display(T->ptr[0], indent + 3);
			break;
		case ARGS:      i = 1;
			while (T) {  //ARGS表示实际参数表达式序列结点，其第一棵子树为其一个实际参数表达式，第二棵子树为剩下的
				struct ASTNode* T0 = T->ptr[0];
				printf("%*c 第 %d 个实际参数表达式：\n", indent, ' ', i++);
				display(T0, indent + 3);
				T = T->ptr[1];
			}
			//                    printf("%*c第%d个实际参数表达式：\n",indent,' ',i);
			  //                  display(T,indent+3);
			printf("\n");
			break;
		}
	}

#endif // SHOW
}
