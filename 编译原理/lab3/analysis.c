#include "def.h"
#define DEBUG 0
#define SHOW 0

int LEV = 0;  //锟斤拷锟斤拷锟剿诧拷锟�??1锟�??7
int flag = 0; //锟斤拷锟斤拷锟斤拷break锟斤拷志

char *strcat0(char *s1, char *s2)
{
	static char result[10];
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

char *newAlias()
{
	static int no = 1;
	char s[10];
	//itoa(no++, s, 10);
	snprintf(s, 10, "%d", no++);
	return strcat0("v", s);
}

char *newLabel()
{
	static int no = 1;
	char s[10];
	//itoa(no++, s, 10);
	snprintf(s, 10, "%d", no++);
	return strcat0("label", s);
}

char *newTemp()
{
	static int no = 1;
	char s[10];
	//	itoa(no++, s, 10);
	snprintf(s, 10, "%d", no++);
	return strcat0("temp", s);
}

//锟斤拷锟斤拷一锟斤拷TAC锟斤拷锟斤拷慕锟斤拷锟斤拷傻锟剿拷锟窖拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟酵分革拷锟�??1锟�??7
struct codenode *genIR(int op, struct opn opn1, struct opn opn2, struct opn result)
{
	struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
	h->op = op;
	h->opn1 = opn1;
	h->opn2 = opn2;
	h->result = result;
	h->next = h->prior = h;
	return h;
}

//锟斤拷锟斤拷一锟斤拷锟斤拷锟斤拷锟戒，锟斤拷锟斤拷头指锟斤拷
struct codenode *genLabel(char *label)
{
	struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
	h->op = LABEL;
	strcpy(h->result.id, label);
	h->next = h->prior = h;
	return h;
}

//锟斤拷锟斤拷GOTO锟斤拷洌拷锟斤拷锟酵分革拷锟�??1锟�??7
struct codenode *genGoto(char *label)
{
	struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
	h->op = GOTO;
	strcpy(h->result.id, label);
	h->next = h->prior = h;
	return h;
}

//锟较诧拷锟斤拷锟斤拷屑锟斤拷锟斤拷锟剿拷锟窖拷锟斤拷锟斤拷锟斤拷锟斤拷锟轿诧拷锟斤拷锟�??1锟�??7
struct codenode *merge(int num, ...)
{
	struct codenode *h1, *h2, *p, *t1, *t2;
	va_list ap;
	va_start(ap, num);
	h1 = va_arg(ap, struct codenode *);
	while (--num > 0)
	{
		h2 = va_arg(ap, struct codenode *);
		if (h1 == NULL)
			h1 = h2;
		else if (h2)
		{
			t1 = h1->prior;
			t2 = h2->prior;
			t1->next = h2;
			t2->next = h1;
			h1->prior = t2;
			h2->prior = t1;
		}
	}
	va_end(ap);
	return h1;
}

//锟斤拷锟斤拷屑锟斤拷锟斤拷
void prnIR(struct codenode *head)
{
	char opnstr1[32], opnstr2[32], resultstr[32];
	struct codenode *h = head;
	FILE *file = fopen("code.txt", "w+");
	do
	{
		if (h->opn1.kind == INT)
			sprintf(opnstr1, "%d", h->opn1.const_int);
		if (h->opn1.kind == FLOAT)
			sprintf(opnstr1, "%f", h->opn1.const_float);
		if (h->opn1.kind == ID)
			sprintf(opnstr1, "%s", h->opn1.id);
		if (h->opn1.kind == CHAR)
			sprintf(opnstr1, "%s", h->opn1.const_char);
		if (h->opn2.kind == INT)
			sprintf(opnstr2, "%d", h->opn2.const_int);
		if (h->opn2.kind == FLOAT)
			sprintf(opnstr2, "%f", h->opn2.const_float);
		if (h->opn2.kind == ID)
			sprintf(opnstr2, "%s", h->opn2.id);
		/*if (h->opn2.kind = CHAR)
			sprintf(opnstr2, "#%s", h->opn2.const_char);*/
		sprintf(resultstr, "%s", h->result.id);
		switch (h->op)
		{
		case ASSIGNOP:
#if show
			printf("%s := %s\n", resultstr, opnstr1);
#endif
			fprintf(file, "%s = %s\n", resultstr, opnstr1);
			break;
		case PLUS:
		case MINUS:
		case STAR:
		case DIV:
		case MOD:
#if show
			printf("  %s := %s %c %s\n", resultstr, opnstr1,
				   h->op == PLUS ? '+' : h->op == MINUS ? '-' : h->op == STAR ? '*' : h->op == DIV ? '/' : '%', opnstr2);
#endif
			fprintf(file, "%s = %s %c %s\n", resultstr, opnstr1,
					h->op == PLUS ? '+' : h->op == MINUS ? '-' : h->op == STAR ? '*' : h->op == DIV ? '/' : '%', opnstr2);
			break;
		case FUNCTION:
#if show
			printf("\nFUNCTION %s :\n", h->result.id);
#endif
			fprintf(file, "FUNCTION %s\n", h->result.id);
			break;
		case PARAM:
#if show
			printf("  PARAM %s\n", h->result.id);
#endif
			fprintf(file, "PARAM %s\n", h->result.id);
			break;
		case LABEL:
#if show
			printf("LABEL %s :\n", h->result.id);
#endif
			fprintf(file, "LABEL %s :\n", h->result.id);
			break;
		case GOTO:
#if show
			printf("  GOTO %s\n", h->result.id);
#endif
			fprintf(file, "GOTO %s\n", h->result.id);
			break;
		case JLE:
#if show
			printf("  IF %s <= %s GOTO %s\n", opnstr1, opnstr2, resultstr);
#endif
			if (h->result.kind == boolean)
				fprintf(file, "%s = %s <= %s\n", resultstr, opnstr1, opnstr2);
			else
				fprintf(file, "IF %s <= %s GOTO %s\n", opnstr1, opnstr2, resultstr);
			break;
		case JLT:
#if show
			printf("  IF %s < %s GOTO %s\n", opnstr1, opnstr2, resultstr);
#endif
			fprintf(file, "IF %s < %s GOTO %s\n", opnstr1, opnstr2, resultstr);
			break;
		case JGE:
#if show
			printf("  IF %s >= %s GOTO %s\n", opnstr1, opnstr2, resultstr);
#endif
			fprintf(file, "IF %s >= %s GOTO %s\n", opnstr1, opnstr2, resultstr);
			break;
		case JGT:
#if show
			printf("  IF %s > %s GOTO %s\n", opnstr1, opnstr2, resultstr);
#endif
			fprintf(file, "IF %s > %s GOTO %s\n", opnstr1, opnstr2, resultstr);
			break;
		case EQ:
#if show
			printf("  IF %s == %s GOTO %s\n", opnstr1, opnstr2, resultstr);
#endif
			fprintf(file, "IF %s == %s GOTO %s\n", opnstr1, opnstr2, resultstr);
			break;
		case NEQ:
#if show
			printf("  IF %s != %s GOTO %s\n", opnstr1, opnstr2, resultstr);
#endif
			fprintf(file, "IF %s != %s GOTO %s\n", opnstr1, opnstr2, resultstr);
			break;
		case ARG:
#if show
			printf("  ARG %s\n", h->result.id);
#endif
			fprintf(file, "ARG %s\n", h->result.id);
			break;
		case CALL:
			if (!strcmp(opnstr1, "write"))
			{
#if show
				printf("  CALL  %s\n", opnstr1);
#endif
				fprintf(file, "CALL  %s\n", opnstr1);
			}
			else
			{
#if show
				printf("  %s := CALL %s\n", resultstr, opnstr1);
#endif
				fprintf(file, "%s = CALL %s\n", resultstr, opnstr1);
			}
			break;
		case RETURN:
			if (h->result.kind)
			{
#if show
				printf("  RETURN %s\n", resultstr);
#endif
				fprintf(file, "RETURN %s\n", resultstr);
			}
			else
			{
#if show
				printf("  RETURN\n");
#endif
				fprintf(file, "RETURN\n");
			}
			break;
		case BLOCK:
#if show
			printf("BLOCK %s :\n", h->result.id);
#endif
			fprintf(file, "BLOCK %s :\n", h->result.id);
			break;
		default:
			break;
		}
		h = h->next;
	} while (h != head);
	fclose(file);
}

//锟斤拷锟斤拷锟斤拷锟街伙拷占锟斤拷锟斤拷锟斤拷锟较拷锟斤拷锟斤拷一锟斤拷锟斤拷示
void semantic_error(int line, char *msg1, char *msg2)
{
	printf("在%d行,%s %s\n", line, msg1, msg2);
}

//锟斤拷示锟斤拷锟脚憋拷
void prn_symbol()
{
	int i = 0;
	//printf("%6s %6s %6s  %6s %4s %6s\n", "锟斤拷锟斤拷锟斤拷", "锟斤拷 锟斤拷", "锟斤拷 锟斤拷", "锟斤拷  锟斤拷", "锟斤拷锟�??1锟�??7", "偏锟斤拷锟斤拷");
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("|                                       Symbol Table                                            |\n");
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("|\t%s\t|\t%s\t|\t%s\t|\t%s\t|\t%s\t|\t%s\t|\n", "变量名", "别名", "层号", "类型", "标记", "偏移量");
	printf("-------------------------------------------------------------------------------------------------\n");
	/*for (i = 0; i < symbolTable.index; i++)
		printf("%6s %6s %6d  %6s %4c %6d\n", symbolTable.symbols[i].name, \
			symbolTable.symbols[i].alias, symbolTable.symbols[i].level, \
			symbolTable.symbols[i].type == INT ? "int" : "float", \
			symbolTable.symbols[i].flag, symbolTable.symbols[i].offset);*/

	for (i = 0; i < symbolTable.index; ++i)
	{
		if (!strcmp(symbolTable.symbols[i].name, " "))
			continue;
		printf("|\t%s\t", symbolTable.symbols[i].name);
		printf("|\t%s\t", symbolTable.symbols[i].alias);
		printf("|\t%d\t", symbolTable.symbols[i].level);
		switch (symbolTable.symbols[i].type)
		{
		case INT:
			if (symbolTable.symbols[i].flag != 'A')
				printf("|\t%s\t", "int");
			else
				printf("|\t%s\t", "int[]");
			break;
		case FLOAT:
			if (symbolTable.symbols[i].flag != 'A')
				printf("|\t%s\t", "float");
			else
				printf("|\t%s\t", "float[]");
			break;
		case CHAR:
			if (symbolTable.symbols[i].flag != 'A')
				printf("|\t%s\t", "char");
			else
				printf("|\t%s\t", "char[]");
			break;
		default:
			break;
		}
		printf("|\t%c\t", (symbolTable.symbols[i].flag));
		/*if (symbolTable.symbols[i].flag == 'F')
			printf("%s %d\t|\n", "Func panramnum:", symbolTable.symbols[i].paramnum);
		else*/
		printf("|\t%d\t|\n", symbolTable.symbols[i].offset);
	}
	printf("-------------------------------------------------------------------------------------------------\n");
}

//锟斤拷锟斤拷锟斤拷锟脚憋拷
int searchSymbolTable(char *name)
{
	int i, flag = 0;
	for (i = symbolTable.index - 1; i >= 0; i--)
	{
		if (symbolTable.symbols[i].level == 0)
			flag = 1;
		if (flag && symbolTable.symbols[i].level == 1)
			continue; //锟斤拷锟斤拷前锟芥函锟斤拷锟斤拷锟斤拷式锟斤拷锟斤拷锟斤拷锟斤拷
		if (!strcmp(symbolTable.symbols[i].name, name))
			return i;
	}
	return -1;
}

//锟斤拷锟斤拷疟锟�??1锟�??7
int fillSymbolTable(char *name, char *alias, int level, int type, char flag, int offset)
{
	//锟斤拷锟饺革拷锟斤拷name锟斤拷锟斤拷疟锟斤拷锟斤拷锟斤拷锟斤拷馗锟斤拷锟斤拷锟�??1锟�??7 锟截革拷锟斤拷锟藉返锟斤拷-1
	int i;
	/*锟斤拷锟脚诧拷锟截ｏ拷锟斤拷锟斤拷锟解部锟斤拷锟斤拷锟斤拷锟斤拷前锟叫猴拷锟斤拷锟斤拷锟藉，
	锟斤拷锟轿诧拷锟斤拷锟斤拷锟节凤拷锟脚憋拷锟叫ｏ拷锟斤拷时锟斤拷锟解部锟斤拷锟斤拷锟斤拷前锟斤拷锟斤拷锟斤拷锟轿诧拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷*/
	for (i = symbolTable.index - 1; i >= 0 && (symbolTable.symbols[i].level == level || level == 0); i--)
	{
		if (level == 0 && symbolTable.symbols[i].level == 1)
			continue; //锟解部锟斤拷锟斤拷锟斤拷锟轿参诧拷锟截比斤拷锟斤拷锟斤拷
		if (!strcmp(symbolTable.symbols[i].name, name))
			return -1;
	}
	//锟斤拷写锟斤拷锟脚憋拷锟斤拷锟斤拷
	strcpy(symbolTable.symbols[symbolTable.index].name, name);
	strcpy(symbolTable.symbols[symbolTable.index].alias, alias);
	symbolTable.symbols[symbolTable.index].level = level;
	symbolTable.symbols[symbolTable.index].type = type;
	symbolTable.symbols[symbolTable.index].flag = flag;
	symbolTable.symbols[symbolTable.index].offset = offset;
	return symbolTable.index++; //锟斤拷锟截碉拷锟角凤拷锟斤拷锟节凤拷锟脚憋拷锟叫碉拷位锟斤拷锟斤拷牛锟斤拷屑锟斤拷锟斤拷锟斤拷锟斤拷时锟斤拷锟斤拷锟斤拷锟饺★拷锟斤拷锟斤拷疟锟斤拷锟�??1锟�??7
}

//锟斤拷写锟斤拷时锟斤拷锟斤拷锟斤拷锟斤拷锟脚憋拷锟斤拷锟斤拷锟斤拷锟斤拷时锟斤拷锟斤拷锟节凤拷锟脚憋拷锟叫碉拷位锟斤拷
int fill_Temp(char *name, int level, int type, char flag, int offset)
{
	strcpy(symbolTable.symbols[symbolTable.index].name, "");
	strcpy(symbolTable.symbols[symbolTable.index].alias, name);
	symbolTable.symbols[symbolTable.index].level = level;
	symbolTable.symbols[symbolTable.index].type = type;
	symbolTable.symbols[symbolTable.index].flag = flag;
	symbolTable.symbols[symbolTable.index].offset = offset;
	return symbolTable.index++; //锟斤拷锟截碉拷锟斤拷锟斤拷时锟斤拷锟斤拷锟节凤拷锟脚憋拷锟叫碉拷位锟斤拷锟斤拷锟�??1锟�??7
}

//锟斤拷锟斤拷锟斤拷锟斤拷锟叫憋拷
void ext_var_list(struct ASTNode *T)
{
	int rtn, num = 1;
	switch (T->kind)
	{
	case EXT_DEC_LIST:
		T->ptr[0]->type = T->type;	   //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟铰达拷锟捷憋拷锟斤拷锟斤拷锟�??1锟�??7
		T->ptr[0]->offset = T->offset; //锟解部锟斤拷锟斤拷锟斤拷偏锟斤拷锟斤拷锟斤拷锟铰达拷锟斤拷
		T->ptr[1]->type = T->type;	   //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟铰达拷锟捷憋拷锟斤拷锟斤拷锟�??1锟�??7
		//T->ptr[1]->offset = T->offset + T->width; //锟解部锟斤拷锟斤拷锟斤拷偏锟斤拷锟斤拷锟斤拷锟铰达拷锟斤拷
		if (T->ptr[0]->kind = ARRAY_DF)
			T->ptr[1]->offset = T->offset + T->width * calArrayNums(T->ptr[0]->ptr[0]);
		else
			T->ptr[1]->offset = T->offset + T->width; //锟解部锟斤拷锟斤拷锟斤拷偏锟斤拷锟斤拷锟斤拷锟铰达拷锟斤拷
		T->ptr[1]->width = T->width;
		ext_var_list(T->ptr[0]);
		ext_var_list(T->ptr[1]);
		T->num = T->ptr[1]->num + T->ptr[0]->num;
		break;
	case ID:
		rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'V', T->offset); //锟斤拷锟揭伙拷锟斤拷锟斤拷锟斤拷锟�??1锟�??7
		if (rtn == -1)
			semantic_error(T->pos, T->type_id, "变量重复定义");
		else
		{
			T->place = rtn;
			T->num = 1;
		}
		break;
	case ARRAY_DF:
		//锟斤拷锟介定锟斤拷
		rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'A', T->offset); //锟斤拷锟揭伙拷锟斤拷锟斤拷锟斤拷锟�??1锟�??7
		if (rtn == -1)
		{
			semantic_error(T->pos, T->type_id, "变量重复定义");
			break;
		}
		struct ASTNode *T0;
		T0 = T->ptr[0];
		while (T0)
		{
			if (T0->ptr[0] && T0->ptr[0]->type_int <= 0 || T0->ptr[0]->type != INT)
			{
				semantic_error(T->pos, T->type_id, "数组下标不能为负值或0");
				return;
			}
			T0 = T0->ptr[1];
		}
		T->place = rtn;
		T->num = calArrayNums(T->ptr[0]);
		break;
	}
}

//锟皆猴拷锟斤拷实锟斤拷锟斤拷锟轿参斤拷锟斤拷锟斤拷锟斤拷锟斤拷
int match_param(int i, struct ASTNode *T)
{
	int j, num = symbolTable.symbols[i].paramnum;
	int type1, type2, pos = T->pos;
	T = T->ptr[0];
	if (num == 0 && T == NULL)
		return 1;
	for (j = 1; j <= num; j++)
	{
		if (!T)
		{
			semantic_error(pos, "", "函数调用参数太少!");
			return 0;
		}
		type1 = symbolTable.symbols[i + j].type; //锟轿诧拷锟斤拷锟斤拷
		type2 = T->ptr[0]->type;
		if (type1 != type2)
		{
			semantic_error(pos, "", "参数类型不匹配");
			return 0;
		}
		T = T->ptr[1];
	}
	if (T)
	{ //num锟斤拷锟斤拷锟斤拷锟窖撅拷匹锟斤拷锟疥，锟斤拷锟斤拷实锟轿憋拷锟斤拷式
		semantic_error(pos, "", "函数调用参数太多!");
		return 0;
	}
	return 1;
}

//锟斤拷锟斤拷锟斤拷锟斤拷式锟斤拷锟轿匡拷锟斤拷锟斤拷[2]p84锟斤拷思锟斤拷
void boolExp(struct ASTNode *T)
{
	struct opn opn1, opn2, result;
	int op;
	int rtn;
	if (T)
	{
		switch (T->kind)
		{
		case INT:
			if (T->type_int != 0)
				T->code = genGoto(T->Etrue);
			else
				T->code = genGoto(T->Efalse);
			T->width = 0;
			break;
		case FLOAT:
			if (T->type_float != 0.0)
				T->code = genGoto(T->Etrue);
			else
				T->code = genGoto(T->Efalse);
			T->width = 0;
			break;
		case CHAR:
			if (T->type_char[0] != '0')
				T->code = genGoto(T->Etrue);
			else
				T->code = genGoto(T->Efalse);
			T->width = 0;
			break;
		/*case ARRAY_DF:
			rtn = searchSymbolTable(T->type_id);
			if (rtn == -1)
				semantic_error(T->pos, T->type_id, "锟斤拷锟斤拷锟斤拷未锟斤拷锟斤拷");
			else if (symbolTable.symbols[rtn].flag == 'F')
				semantic_error(T->pos, T->type_id, "锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷,锟斤拷锟酵诧拷匹锟斤拷");
			else if (symbolTable.symbols[rtn].flag == 'V')
				semantic_error(T->pos, T->type_id, "锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷筒锟狡ワ拷锟�??1锟�??7");
			else
			{
				T->place = rtn; //锟斤拷惚ｏ拷锟斤拷锟斤拷锟节凤拷锟脚憋拷锟叫碉拷位锟斤拷
				T->type = symbolTable.symbols[rtn].type;
			}
			T->type = INT;
			break;*/
		case ID:
			//锟斤拷要锟斤拷锟斤拷疟锟斤拷锟斤拷业锟斤拷锟斤拷疟锟斤拷械锟轿伙拷茫锟斤拷锟斤拷锟絋ype
			rtn = searchSymbolTable(T->type_id);
			if (rtn == -1)
				semantic_error(T->pos, T->type_id, "变量未定义");
			if (symbolTable.symbols[rtn].flag == 'F')
				semantic_error(T->pos, T->type_id, "定义为函数名,类型不匹配");
			else if (symbolTable.symbols[rtn].flag == 'A')
				semantic_error(T->pos, T->type_id, "定义为数组名,类型不匹配");
			else
			{
				opn1.kind = ID;
				strcpy(opn1.id, symbolTable.symbols[rtn].alias);
				opn1.offset = symbolTable.symbols[rtn].offset;
				opn2.kind = INT;
				opn2.const_int = 0;
				result.kind = ID;
				strcpy(result.id, T->Etrue);
				T->code = genIR(NEQ, opn1, opn2, result);
				T->code = merge(2, T->code, genGoto(T->Efalse));
			}
			T->width = 0;
			break;
		case RELOP: //锟斤拷锟斤拷锟斤拷系锟斤拷锟斤拷锟斤拷锟斤拷?1锟�??7,2锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷式锟斤拷锟斤拷
			T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
			Exp(T->ptr[0]);
			T->width = T->ptr[0]->width;
			Exp(T->ptr[1]);
			if (T->width < T->ptr[1]->width)
				T->width = T->ptr[1]->width;
			opn1.kind = ID;
			strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
			opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
			opn2.kind = ID;
			strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
			opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
			result.kind = ID;
			strcpy(result.id, T->Etrue);
			if (strcmp(T->type_id, "<") == 0)
				op = JLT;
			else if (strcmp(T->type_id, "<=") == 0)
				op = JLE;
			else if (strcmp(T->type_id, ">") == 0)
				op = JGT;
			else if (strcmp(T->type_id, ">=") == 0)
				op = JGE;
			else if (strcmp(T->type_id, "==") == 0)
				op = EQ;
			else if (strcmp(T->type_id, "!=") == 0)
				op = NEQ;
			T->code = genIR(op, opn1, opn2, result);
			T->code = merge(4, T->ptr[0]->code, T->ptr[1]->code, T->code, genGoto(T->Efalse));
			break;
		case AND:
		case OR:
			if (T->kind == AND)
			{
				strcpy(T->ptr[0]->Etrue, newLabel());
				strcpy(T->ptr[0]->Efalse, T->Efalse);
			}
			else
			{
				strcpy(T->ptr[0]->Etrue, T->Etrue);
				strcpy(T->ptr[0]->Efalse, newLabel());
			}
			strcpy(T->ptr[1]->Etrue, T->Etrue);
			strcpy(T->ptr[1]->Efalse, T->Efalse);
			T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
			boolExp(T->ptr[0]);
			T->width = T->ptr[0]->width;
			boolExp(T->ptr[1]);
			if (T->width < T->ptr[1]->width)
				T->width = T->ptr[1]->width;
			if (T->kind == AND)
				T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code);
			else
				T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Efalse), T->ptr[1]->code);
			break;
		case NOT:
			strcpy(T->ptr[0]->Etrue, T->Efalse);
			strcpy(T->ptr[0]->Efalse, T->Etrue);
			boolExp(T->ptr[0]);
			T->code = T->ptr[0]->code;
			break;
		default:
			break;
		}
	}
}

//锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷式锟斤拷锟轿匡拷锟斤拷锟斤拷[2]p82锟斤拷思锟斤拷
void Exp(struct ASTNode *T)
{
	int rtn, num, width, op;
	struct ASTNode *T0;
	struct opn opn1, opn2, result;
	if (T)
	{
		switch (T->kind)
		{
		case ID:
			//锟斤拷锟斤拷疟锟斤拷锟斤拷锟矫凤拷锟脚憋拷锟叫碉拷位锟矫ｏ拷锟斤拷锟斤拷锟斤拷type
			rtn = searchSymbolTable(T->type_id);
			if (rtn == -1)
				semantic_error(T->pos, T->type_id, "变量未定义");
			if (symbolTable.symbols[rtn].flag == 'F')
				semantic_error(T->pos, T->type_id, "是函数名，类型不匹配");
			/*else if (symbolTable.symbols[rtn].flag == 'A')
				semantic_error(T->pos, T->type_id, "是数组变量,类型不匹配");*/
			else
			{
				T->place = rtn; //锟斤拷惚ｏ拷锟斤拷锟斤拷锟节凤拷锟脚憋拷锟叫碉拷位锟斤拷
				T->code = NULL; //锟斤拷识锟斤拷锟斤拷锟斤拷要锟斤拷锟斤拷TAC
				T->type = symbolTable.symbols[rtn].type;
				T->offset = symbolTable.symbols[rtn].offset;
				T->width = 0; //未锟斤拷使锟斤拷锟铰碉拷元
			}
			break;
		case INT:
			T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset); //为锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷一锟斤拷锟斤拷时锟斤拷锟斤拷
			T->type = INT;
			opn1.kind = INT;
			opn1.const_int = T->type_int;
			result.kind = ID;
			strcpy(result.id, symbolTable.symbols[T->place].alias);
			result.offset = symbolTable.symbols[T->place].offset;
			T->code = genIR(ASSIGNOP, opn1, opn2, result);
			T->width = 4;
			break;
		case FLOAT:
			T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset); //为锟斤拷锟姐常锟斤拷锟斤拷锟斤拷一锟斤拷锟斤拷时锟斤拷锟斤拷
			T->type = FLOAT;
			opn1.kind = FLOAT;
			opn1.const_float = T->type_float;
			result.kind = ID;
			strcpy(result.id, symbolTable.symbols[T->place].alias);
			result.offset = symbolTable.symbols[T->place].offset;
			T->code = genIR(ASSIGNOP, opn1, opn2, result);
			T->width = 4;
			break;
		case CHAR:
			T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
			//为锟街凤拷锟斤拷锟斤拷锟斤拷锟斤拷一锟斤拷锟斤拷时锟斤拷锟斤拷
			T->type = CHAR;
			opn1.kind = CHAR;
			strcpy(opn1.const_char, T->type_char);
			//opn1.const_char = T->type_char;
			result.kind = ID;
			strcpy(result.id, symbolTable.symbols[T->place].alias);
			result.offset = symbolTable.symbols[T->place].offset;
			T->code = genIR(ASSIGNOP, opn1, opn2, result);
			T->width = 4;
			break;
		case ARRAY_DF:
			//锟斤拷锟斤拷疟锟�??1锟�??7
			rtn = searchSymbolTable(T->type_id);
			if (rtn == -1)
				semantic_error(T->pos, T->type_id, "数组未定义");
			else if (symbolTable.symbols[rtn].flag == 'F')
				semantic_error(T->pos, T->type_id, "为函数名，类型不匹配");
			else if (symbolTable.symbols[rtn].flag == 'V')
				semantic_error(T->pos, T->type_id, "不是数组变量，类型不匹配");
			else
			{

				T0 = T->ptr[0];
				while (T0->ptr[0])
				{
					if (T0->ptr[0]->type_int <= 0 || T0->ptr[0]->type != INT)
					{
						semantic_error(T->pos, T->type_id, "数组下标非法");
						return;
					}
					T0 = T0->ptr[1];
				}

				T->place = rtn;
				T->type = symbolTable.symbols[rtn].type;
			}
			break;
		case ASSIGNOP:
			if (T->ptr[0]->kind != ID && T->ptr[0]->kind != ARRAY_DF && T->ptr[0]->kind != ARRAY_CALL)
			{
				semantic_error(T->pos, "", "赋值语句需要左值");
				break;
			}
			else
			{
				Exp(T->ptr[0]); //处理左值，例中仅为变量
				T->ptr[1]->offset = T->offset;
				Exp(T->ptr[1]);
				if (T->ptr[0]->type != T->ptr[1]->type && T->ptr[0]->kind != ARRAY_CALL)
				{
					semantic_error(T->pos, "", "赋值号两边的类型不匹配");
					break;
				}
				if (T->ptr[0]->type == CHAR && T->kind != ASSIGNOP)
				{
					semantic_error(T->pos, T->ptr[0]->type_id, "字符类型变量不能参与运算");
					break;
				}
				if (T->ptr[1]->type == CHAR && T->kind != ASSIGNOP)
				{
					semantic_error(T->pos, T->ptr[1]->type_id, "字符类型变量不能参与运算");
					break;
				}
				T->type = T->ptr[0]->type;
				T->width = T->ptr[1]->width;
				T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code);
				opn1.kind = ID;
				if (T->ptr[1]->kind != ARRAY_CALL)
				{
					strcpy(opn1.id, symbolTable.symbols[T->ptr[1]->place].alias); //右值一定是个变量或临时变量
					opn1.offset = symbolTable.symbols[T->ptr[1]->place].offset;
				}
				else
				{
					char alias[20];
					//左右都不考虑多维了
					strcpy(alias, symbolTable.symbols[T->ptr[1]->place].alias);
					strcat(alias, "[");
					strcat(alias, symbolTable.symbols[T->ptr[1]->ptr[0]->place].alias);
					strcat(alias, "]");
					strcpy(opn1.id, alias);
					opn1.offset = T->ptr[1]->offset;
				}
				result.kind = ID;
				if (T->ptr[0]->kind == ID)
				{
					strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
					result.offset = symbolTable.symbols[T->ptr[0]->place].offset;
				}
				else /*if(T->ptr[0]->kind == ARRAY_CALL)*/
				{
					char alias[20];
					strcpy(alias, symbolTable.symbols[T->ptr[0]->place].alias);
					strcat(alias, "[");
					//先暂时不考虑多维数组的访问问题，太头疼了
					strcat(alias, symbolTable.symbols[T->ptr[0]->ptr[0]->place].alias);
					strcat(alias, "]");
					strcpy(result.id, alias);
					result.offset = T->ptr[0]->offset;
				}
				T->code = merge(2, T->code, genIR(ASSIGNOP, opn1, opn2, result));
			}
			break;
		case AND:
		case OR:
			Exp(T->ptr[0]);
			Exp(T->ptr[1]);
			break;
		case RELOP:
			if (strcmp(T->type_id, "<") == 0)
				op = JLT;
			else if (strcmp(T->type_id, "<=") == 0)
				op = JLE;
			else if (strcmp(T->type_id, ">") == 0)
				op = JGT;
			else if (strcmp(T->type_id, ">=") == 0)
				op = JGE;
			else if (strcmp(T->type_id, "==") == 0)
				op = EQ;
			else if (strcmp(T->type_id, "!=") == 0)
				op = NEQ;
			T->type = INT;
			//处理关系运算表达式,2个操作数都按基本表达式处理
			T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
			Exp(T->ptr[0]);
			T->width = T->ptr[0]->width;
			Exp(T->ptr[1]);
			break;
		case PLUS:
		case MINUS:
		case STAR:
		case DIV:
		case MOD:
			T->ptr[0]->offset = T->offset;
			Exp(T->ptr[0]);
			T->ptr[1]->offset = T->offset + T->ptr[0]->width;
			Exp(T->ptr[1]);
			//锟叫讹拷T->ptr[0]锟斤拷T->ptr[1]锟斤拷锟斤拷锟角凤拷锟斤拷确锟斤拷锟斤拷锟杰革拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷刹锟酵拷锟绞斤拷拇锟斤拷耄拷锟絋锟斤拷type锟斤拷值
			//锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷约锟斤拷悖伙拷锌锟斤拷谴锟斤拷锟斤拷锟斤拷锟斤拷
			if (T->ptr[0]->type == CHAR)
			{
				semantic_error(T->pos, T->ptr[0]->type_id, "是字符类型变量，不能参与运算");
				break;
			}
			else if (T->ptr[1]->type == CHAR)
			{
				semantic_error(T->pos, T->ptr[1]->type_id, "是字符类型变量，不能参与运算");
				break;
			}
			if (T->ptr[0]->type == FLOAT && T->ptr[1]->type == FLOAT)
				T->type = FLOAT, T->width = T->ptr[0]->width + T->ptr[1]->width + 4;
			else if (T->ptr[0]->type == INT && T->ptr[1]->type == INT)
				T->type = INT, T->width = T->ptr[0]->width + T->ptr[1]->width + 2;
			else
			{
				semantic_error(T->pos, "", "运算符左右变量类型不匹配");
				break;
			}
			T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->ptr[0]->width + T->ptr[1]->width);
			opn1.kind = ID;
			strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
			opn1.type = T->ptr[0]->type;
			opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
			opn2.kind = ID;
			strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
			opn2.type = T->ptr[1]->type;
			opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
			result.kind = ID;
			strcpy(result.id, symbolTable.symbols[T->place].alias);
			result.type = T->type;
			result.offset = symbolTable.symbols[T->place].offset;
			T->code = merge(3, T->ptr[0]->code, T->ptr[1]->code, genIR(T->kind, opn1, opn2, result));
			T->width = T->ptr[0]->width + T->ptr[1]->width + (T->type == INT ? 4 : 8);
			break;
		case NOT: //未写锟斤拷锟斤拷
			Exp(T->ptr[0]);
			T->type = INT;
			T->ptr[0]->offset = T->offset;
			break;
		case UMINUS:
			Exp(T->ptr[0]);
			T->type = T->ptr[0]->type;
			T->ptr[0]->offset = T->offset;
			break;
		case AUTOADD:
			if (T->ptr[0])
			{
				if (T->ptr[0]->kind != ID && T->ptr[0]->kind != ARRAY_DF && T->ptr[0]->kind != ARRAY_CALL)
				{
					semantic_error(T->pos, "", "自增语句需要左值");
					break;
				}
				Exp(T->ptr[0]);
				rtn = searchSymbolTable(T->ptr[0]->type_id);
				if (rtn == -1)
				{
					semantic_error(T->pos, T->type_id, "变量未定义");
					break;
				}
				if (symbolTable.symbols[rtn].flag == 'F')
				{
					semantic_error(T->pos, T->type_id, "是函数名，类型不匹配");
					break;
				}
				if (symbolTable.symbols[rtn].type != INT)
				{
					semantic_error(T->pos, "", "自增语句左值不为int型");
					break;
				}
				op = PLUS;
				T->type = T->ptr[0]->type;
				T->ptr[0]->offset = T->offset;

				struct ASTNode temp; //锟斤拷锟斤拷一锟斤拷锟斤拷时锟斤拷锟斤拷
				T->ptr[1] = &temp;
				T->ptr[1]->kind = INT;
				T->ptr[1]->type_int = 1; //锟斤拷锟斤拷1
				T->ptr[1]->offset = T->offset + T->ptr[0]->width + 4;
				Exp(T->ptr[1]);
				T->width = T->ptr[0]->width + 2;
				T->place = T->ptr[0]->place;
				opn1.kind = ID;
				strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
				opn1.type = T->ptr[0]->type;
				opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
				opn2.kind = ID;
				strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
				opn2.type = T->ptr[1]->type;
				opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
				//锟斤拷锟�??1锟�??7
				result.kind = ID;
				strcpy(result.id, symbolTable.symbols[T->place].alias);
				result.type = T->type;
				result.offset = symbolTable.symbols[T->place].offset;
				T->code = merge(3, T->ptr[0]->code, T->ptr[1]->code, genIR(op, opn1, opn2, result));
				T->width = T->ptr[0]->width + T->ptr[1]->width + 4;
			}
			/*else if (T->ptr[1]) {
				Exp(T->ptr[1]);
				if (T->ptr[1]->kind != ID && T->ptr[1]->kind != ARRAY_DF ) {
					semantic_error(T->pos, "", "锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟揭拷锟斤拷?1锟�??7");
				}
				if (T->ptr[1]->type != INT) {
					semantic_error(T->pos, "", "锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟街碉拷锟轿猧nt锟斤拷");
				}
				T->type = T->ptr[1]->type;
				T->ptr[1]->offset = T->offset;
			}*/
			break;
		case AUTOSUB:
			if (T->ptr[0])
			{
				if (T->ptr[0]->kind != ID && T->ptr[0]->kind != ARRAY_DF && T->ptr[0]->kind != ARRAY_CALL)
				{
					semantic_error(T->pos, "", "自减语句需要左值");
					break;
				}
				Exp(T->ptr[0]);
				rtn = searchSymbolTable(T->ptr[0]->type_id);
				if (rtn == -1)
				{
					semantic_error(T->pos, T->type_id, "变量未定义");
					break;
				}
				if (symbolTable.symbols[rtn].flag == 'F')
				{
					semantic_error(T->pos, T->type_id, "是函数名，类型不匹配");
					break;
				}
				if (symbolTable.symbols[rtn].type != INT)
				{
					semantic_error(T->pos, "", "自减语句左值不为int型");
					break;
				}

				T->type = T->ptr[0]->type;
				T->ptr[0]->offset = T->offset;

				op = MINUS;
				Exp(T->ptr[0]);
				T->type = T->ptr[0]->type;
				T->ptr[0]->offset = T->offset;

				struct ASTNode temp; //锟斤拷锟斤拷一锟斤拷锟斤拷时锟斤拷锟斤拷
				T->ptr[1] = &temp;
				T->ptr[1]->kind = INT;
				T->ptr[1]->type_int = 1; //锟斤拷锟斤拷1
				T->ptr[1]->offset = T->offset + T->ptr[0]->width + 4;
				Exp(T->ptr[1]);
				T->width = T->ptr[0]->width + 2;
				//锟斤拷锟斤拷锟斤拷式锟斤拷锟斤拷
				T->place = T->ptr[0]->place;
				opn1.kind = ID;
				strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
				opn1.type = T->ptr[0]->type;
				opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
				opn2.kind = ID;
				strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
				opn2.type = T->ptr[1]->type;
				opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
				//锟斤拷锟�??1锟�??7
				result.kind = ID;
				strcpy(result.id, symbolTable.symbols[T->place].alias);
				result.type = T->type;
				result.offset = symbolTable.symbols[T->place].offset;
				T->code = merge(3, T->ptr[0]->code, T->ptr[1]->code, genIR(op, opn1, opn2, result));
				T->width = T->ptr[0]->width + T->ptr[1]->width + 4;
			}
			/*else if (T->ptr[1]){
				Exp(T->ptr[1]);
				if (T->ptr[1]->kind != ID && T->ptr[1]->kind != ARRAY_DF) {
					semantic_error(T->pos, "", "锟斤拷锟皆硷拷锟斤拷锟斤拷锟揭拷锟斤拷?1锟�??7");
				}
				if (T->ptr[1]->type != INT) {
					semantic_error(T->pos, "", "锟斤拷锟皆硷拷锟斤拷锟斤拷锟街碉拷锟轿猧nt锟斤拷");
				}
				T->type = T->ptr[1]->type;
				T->ptr[1]->offset = T->offset;
			}*/
			break;
		case COMADD:
		case COMSUB:
		case COMDIV:
		case COMSTAR:
		case COMMOD:
			if (T->ptr[0]->kind != ID && T->ptr[0]->kind != ARRAY_DF && T->ptr[0]->kind != ARRAY_CALL)
			{
				semantic_error(T->pos, "", "复合赋值语句需要左值");
				break;
			}
			if (T->ptr[0]->type == CHAR)
			{
				semantic_error(T->pos, T->ptr[0]->type_id, "是字符类型变量，不能参与复合赋值运算");
				break;
			}
			if (T->ptr[1]->type == CHAR)
			{
				semantic_error(T->pos, "", "字符类型变量不能参与复合赋值运算");
				break;
			}
			switch (T->kind)
			{
			case COMADD:
				op = PLUS;
				break;
			case COMSUB:
				op = MINUS;
				break;
			case COMSTAR:
				op = STAR;
				break;
			case COMDIV:
				op = DIV;
				break;
			case COMMOD:
				op = MOD;
				break;
			default:
				break;
			}
			T->ptr[0]->offset = T->offset;
			Exp(T->ptr[0]);
			T->ptr[1]->offset = T->offset + T->ptr[0]->width;
			Exp(T->ptr[1]);
			if (T->ptr[0]->type == FLOAT && T->ptr[1]->type == FLOAT)
			{
				T->type = FLOAT;
			}
			else if (T->ptr[0]->type == INT && T->ptr[1]->type == INT)
			{
				T->type = INT;
			}
			else
			{
				semantic_error(T->pos, "", "复合赋值运算左右变量类型不匹配");
				break;
			}

			T->place = T->ptr[0]->place;
			T->width = T->ptr[0]->width + T->ptr[1]->width;

			opn1.kind = ID;
			strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
			opn1.type = T->ptr[0]->type;
			opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
			opn2.kind = ID;
			strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
			opn2.type = T->ptr[1]->type;
			opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
			result.kind = ID;
			strcpy(result.id, symbolTable.symbols[T->place].alias);
			result.type = T->type;
			result.offset = symbolTable.symbols[T->place].offset;
			T->code = merge(3, T->ptr[0]->code, T->ptr[1]->code, genIR(op, opn1, opn2, result));
			T->width = T->ptr[0]->width + T->ptr[1]->width;
			break;
		case FUNC_CALL: //锟斤拷锟斤拷T->type_id锟斤拷锟斤拷锟斤拷锟斤拷亩锟斤拷澹拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷实锟斤拷滩牡锟絩ead锟斤拷write锟斤拷要锟斤拷锟斤拷锟斤拷锟斤拷一锟斤拷
			rtn = searchSymbolTable(T->type_id);
			if (rtn == -1)
			{
				semantic_error(T->pos, T->type_id, "函数未定义");
				break;
			}
			if (symbolTable.symbols[rtn].flag != 'F')
			{
				semantic_error(T->pos, T->type_id, "不是函数名，不能调用函数");
				break;
			}
			T->type = symbolTable.symbols[rtn].type;
			width = T->type == INT ? 4 : 8; //锟斤拷藕锟斤拷锟斤拷锟斤拷锟街碉拷牡锟斤拷锟斤拷纸锟斤拷锟�??1锟�??7
			if (T->ptr[0])
			{
				T->ptr[0]->offset = T->offset;
				Exp(T->ptr[0]);						 //锟斤拷锟斤拷锟斤拷锟斤拷实锟轿憋拷锟斤拷式锟斤拷值锟斤拷锟斤拷锟斤拷锟斤拷
				T->width = T->ptr[0]->width + width; //锟桔硷拷锟较硷拷锟斤拷实锟斤拷使锟斤拷锟斤拷时锟斤拷锟斤拷锟侥碉拷元锟斤拷
				T->code = T->ptr[0]->code;
			}
			else
			{
				T->width = width;
				T->code = NULL;
				//semantic_error(T->pos, T->type_id, "锟矫猴拷锟斤拷锟斤拷要锟斤拷锟斤拷");
			}
			match_param(rtn, T); //锟斤拷锟斤拷锟斤拷锟叫诧拷锟斤拷锟斤拷匹锟斤拷
			//锟斤拷锟斤拷锟斤拷锟斤拷锟叫憋拷锟斤拷锟叫硷拷锟斤拷锟�??1锟�??7
			T0 = T->ptr[0];
			while (T0)
			{
				result.kind = ID;
				strcpy(result.id, symbolTable.symbols[T0->ptr[0]->place].alias);
				result.offset = symbolTable.symbols[T0->ptr[0]->place].offset;
				T->code = merge(2, T->code, genIR(ARG, opn1, opn2, result));
				T0 = T0->ptr[1];
			}
			T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->width - width);
			opn1.kind = ID;
			strcpy(opn1.id, T->type_id); //锟斤拷锟芥函锟斤拷锟斤拷
			opn1.offset = rtn;			 //锟斤拷锟斤拷offset锟斤拷锟皆憋拷锟芥函锟斤拷锟斤拷锟斤拷锟斤拷锟�??1锟�??7,锟斤拷目锟斤拷锟斤拷锟斤拷锟斤拷锟绞憋拷锟斤拷芑锟饺★拷锟接︼拷锟斤拷?1锟�??7
			result.kind = ID;
			strcpy(result.id, symbolTable.symbols[T->place].alias);
			result.offset = symbolTable.symbols[T->place].offset;
			T->code = merge(2, T->code, genIR(CALL, opn1, opn2, result)); //锟斤拷锟缴猴拷锟斤拷锟斤拷锟斤拷锟叫硷拷锟斤拷锟�??1锟�??7
			break;
		case ARRAY_CALL:
			rtn = searchSymbolTable(T->type_id);
			if (rtn == -1)
			{
				semantic_error(T->pos, T->ptr[0]->type_id, "数组未定义");
				break;
			}
			else if (symbolTable.symbols[rtn].flag == 'F')
			{
				semantic_error(T->pos, T->ptr[0]->type_id, "是函数名，不能采用下标访问");
				break;
			}
			else if (symbolTable.symbols[rtn].flag == 'V')
			{
				semantic_error(T->pos, T->ptr[0]->type_id, "不是数组变量名，不能采用下标访问");
				break;
			}
			T->type = symbolTable.symbols[rtn].type;
			T->place = rtn;
			T->code = NULL;
			T->offset = symbolTable.symbols[rtn].offset + (T->type == INT ? 4 : 8) * calArrayWidth(T->ptr[0], symbolTable.symbols[rtn].array, 0); // 内存中偏移值
			T->width = 0;
			T0 = T->ptr[0];
			int index = 0;
			/*Exp(T->ptr[0]);
			Exp(T->ptr[1]);
			callArray(T->ptr[0]);
			callArray(T->ptr[1]);*/
			while (T0->kind == ARRAY_DEC)
			{
				Exp(T0->ptr[0]);
				if (T0->ptr[0]->type != INT)
				{
					semantic_error(T->pos, "", "数组维数需要整型");
					break;
				}
				if (index >= ARRAY_LEN)
				{
					semantic_error(T->pos, "", "数组维度超过最大值");
					break;
				}
				/*if(symbolTable.symbols[rtn].array[index] <= T0->ptr[0]->type_int){
					semantic_error(T->pos,"", "数组维度超过定义值");
					break;
				}*/
				index++;
				T0 = T0->ptr[1];
			}
			//处理最后一维
			if (T0->kind != ARRAY_DEC)
			{
				Exp(T0);
				if (T0->type != INT)
				{
					semantic_error(T->pos, "", "数组维数需要整型");
					break;
				}
				else if (index >= ARRAY_LEN)
				{
					semantic_error(T->pos, "", "数组维度超过最大值");
					break;
				}
				/*else if(symbolTable.symbols[rtn].array[index] <= T0->type_int){
							semantic_error(T->pos,"", "数组维度超过定义值");
							break;
						}*/
				else if (symbolTable.symbols[rtn].array[index + 1] > 0 && index < ARRAY_LEN)
				{
					semantic_error(T->pos, "", "数组维度未满");
				}
			}
			break;
		case ARGS: //锟剿达拷锟斤拷锟斤拷锟斤拷锟斤拷实锟轿憋拷锟斤拷式锟斤拷锟斤拷值锟侥达拷锟斤拷锟斤拷锟叫ｏ拷锟斤拷锟斤拷锟斤拷ARG锟斤拷实锟斤拷系锟斤拷
			T->ptr[0]->offset = T->offset;
			Exp(T->ptr[0]);
			T->width = T->ptr[0]->width;
			T->code = T->ptr[0]->code;
			if (T->ptr[1])
			{
				T->ptr[1]->offset = T->offset + T->ptr[0]->width;
				Exp(T->ptr[1]);
				T->width += T->ptr[1]->width;
				T->code = merge(2, T->code, T->ptr[1]->code);
			}
			break;
		}
	}
}

void semantic_Analysis(struct ASTNode *T)
{ //锟皆筹拷锟斤拷锟斤法锟斤拷锟斤拷锟饺革拷锟斤拷锟斤拷,锟斤拷display锟侥匡拷锟狡结构锟睫革拷锟斤拷煞锟斤拷疟锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷TAC锟斤拷锟缴ｏ拷锟斤拷洳匡拷郑锟�??1锟�??7
	int rtn, num, width;
	struct ASTNode *T0;
	struct opn opn1, opn2, result;
	if (T)
	{
		switch (T->kind)
		{
		case EXT_DEF_LIST:
			if (!T->ptr[0])
				break;
			// 锟斤拷锟斤拷锟斤拷锟街帮拷锟斤拷锟狡拷频锟斤拷?1锟�??7
			T->ptr[0]->offset = T->offset;
			semantic_Analysis(T->ptr[0]); //锟斤拷锟斤拷锟解部锟斤拷锟斤拷锟叫憋拷锟叫的碉拷一锟斤拷
			T->code = T->ptr[0]->code;

			if (T->ptr[1])
			{
				T->ptr[1]->offset = T->ptr[0]->offset + T->ptr[0]->width;
				semantic_Analysis(T->ptr[1]); //锟斤拷锟绞革拷锟解部锟斤拷锟斤拷锟叫憋拷锟叫碉拷锟斤拷锟斤拷锟解部锟斤拷锟斤拷
				T->code = merge(2, T->code, T->ptr[1]->code);
			}
			break;
		case EXT_VAR_DEF:
			//锟斤拷锟斤拷锟解部说锟斤拷,锟斤拷锟斤拷一锟斤拷锟斤拷锟斤拷(TYPE锟斤拷锟�??1锟�??7)锟叫碉拷锟斤拷锟斤拷锟酵碉拷锟节讹拷锟斤拷锟斤拷锟接碉拷锟斤拷锟斤拷锟斤拷
			//T->type = T->ptr[1]->type = !strcmp(T->ptr[0]->type_id, "int") ? INT : FLOAT;
			if (!strcmp(T->ptr[0]->type_id, "int"))
			{
				T->type = T->ptr[1]->type = INT;
				T->ptr[1]->width = 4;
			}
			if (!strcmp(T->ptr[0]->type_id, "float"))
			{
				T->type = T->ptr[1]->type = FLOAT;
				T->ptr[1]->width = 8;
			}
			if (!strcmp(T->ptr[0]->type_id, "char"))
			{
				T->type = T->ptr[1]->type = CHAR;
				T->ptr[1]->width = 1;
			}
			T->ptr[1]->offset = T->offset;					//锟斤拷锟斤拷獠匡拷锟斤拷锟斤拷锟狡拷锟斤拷锟斤拷锟斤拷麓锟斤拷锟�??1锟�??7
			T->ptr[1]->width = T->type == INT ? 4 : 8;		//锟斤拷一锟斤拷锟斤拷锟斤拷锟侥匡拷锟斤拷锟斤拷锟铰达拷锟斤拷
			ext_var_list(T->ptr[1]);						//锟斤拷锟斤拷锟解部锟斤拷锟斤拷说锟斤拷锟叫的憋拷识锟斤拷锟斤拷锟斤拷
			T->width = (T->ptr[1]->width) * T->ptr[1]->num; //锟斤拷锟斤拷锟斤拷锟斤拷獠匡拷锟斤拷锟剿碉拷锟斤拷目锟斤拷锟�??1锟�??7
			T->code = NULL;									//锟斤拷锟斤拷俣锟斤拷獠匡拷锟斤拷锟斤拷锟街э拷殖锟绞硷拷锟�??1锟�??7
			break;
		case FUNC_DEF: //锟斤拷写锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷息锟斤拷锟斤拷锟脚憋拷
			if (!strcmp(T->ptr[0]->type_id, "int"))
			{
				T->ptr[1]->type = INT;
			}
			if (!strcmp(T->ptr[0]->type_id, "float"))
			{
				T->ptr[1]->type = FLOAT;
			}
			if (!strcmp(T->ptr[0]->type_id, "char"))
			{
				T->ptr[1]->type = CHAR;
			}
			//T->ptr[1]->type = !strcmp(T->ptr[0]->type_id, "int") ? INT : FLOAT;//锟斤拷取锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟酵碉拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟侥斤拷锟�??1锟�??7
			T->width = 0;				   //锟斤拷锟斤拷锟侥匡拷锟斤拷锟斤拷锟斤拷为0锟斤拷锟斤拷锟斤拷锟斤拷獠匡拷锟斤拷锟斤拷牡锟街凤拷锟斤拷锟斤拷锟斤拷影锟斤拷
			T->offset = DX;				   //锟斤拷锟矫局诧拷锟斤拷锟斤拷锟节活动锟斤拷录锟叫碉拷偏锟斤拷锟斤拷锟斤拷值
			semantic_Analysis(T->ptr[1]);  //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟酵诧拷锟斤拷锟斤拷悴匡拷郑锟斤拷锟斤拷锊伙拷锟斤拷锟斤拷眉拇锟斤拷锟斤拷锟斤拷莶锟斤拷锟�??1锟�??7
			T->offset += T->ptr[1]->width; //锟斤拷锟轿参碉拷元锟斤拷锟斤拷锟睫改猴拷锟斤拷锟街诧拷锟斤拷锟斤拷锟斤拷锟斤拷始偏锟斤拷锟斤拷
			T->ptr[2]->offset = T->offset;
			strcpy(T->ptr[2]->Snext, newLabel()); //锟斤拷锟斤拷锟斤拷锟斤拷锟街达拷薪锟斤拷锟斤拷锟斤拷位锟斤拷锟斤拷锟斤拷
			semantic_Analysis(T->ptr[2]);		  //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
			//锟斤拷锟斤拷疃拷锟铰硷拷锟斤拷?1锟�??7,锟斤拷锟斤拷offset锟斤拷锟皆达拷诺锟斤拷腔疃拷锟铰硷拷锟叫★拷锟斤拷锟斤拷锟狡拷锟�??1锟�??7
			symbolTable.symbols[T->ptr[1]->place].offset = T->offset + T->ptr[2]->width;
			T->code = merge(3, T->ptr[1]->code, T->ptr[2]->code, genLabel(T->ptr[2]->Snext)); //锟斤拷锟斤拷锟斤拷拇锟斤拷锟斤拷锟轿拷锟斤拷锟斤拷拇锟斤拷锟�??1锟�??7
			break;
		case FUNC_DEC:															 //锟斤拷锟捷凤拷锟斤拷锟斤拷锟酵ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷写锟斤拷锟脚憋拷
			rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'F', 0); //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟叫凤拷锟戒单元锟斤拷偏锟斤拷锟斤拷为0
			if (rtn == -1)
			{
				semantic_error(T->pos, T->type_id, "函数重复定义");
				break;
			}
			else
				T->place = rtn;
			result.kind = ID;
			strcpy(result.id, T->type_id);
			result.offset = rtn;
			T->code = genIR(FUNCTION, opn1, opn2, result); //锟斤拷锟斤拷锟叫硷拷锟斤拷耄篎UNCTION 锟斤拷锟斤拷锟斤拷
			T->offset = DX;								   //锟斤拷锟斤拷锟斤拷式锟斤拷锟斤拷锟节活动锟斤拷录锟叫碉拷偏锟斤拷锟斤拷锟斤拷值
			if (T->ptr[0])
			{ //锟叫讹拷锟角凤拷锟叫诧拷锟斤拷
				T->ptr[0]->offset = T->offset;
				semantic_Analysis(T->ptr[0]); //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟叫憋拷
				T->width = T->ptr[0]->width;
				symbolTable.symbols[rtn].paramnum = T->ptr[0]->num;
				T->code = merge(2, T->code, T->ptr[0]->code); //锟斤拷锟接猴拷锟斤拷锟斤拷锟酵诧拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
			}
			else
				symbolTable.symbols[rtn].paramnum = 0, T->width = 0;
			break;
		case PARAM_LIST: //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷式锟斤拷锟斤拷锟叫憋拷
			T->ptr[0]->offset = T->offset;
			semantic_Analysis(T->ptr[0]);
			if (T->ptr[1])
			{
				T->ptr[1]->offset = T->offset + T->ptr[0]->width;
				semantic_Analysis(T->ptr[1]);
				T->num = T->ptr[0]->num + T->ptr[1]->num;			  //统锟狡诧拷锟斤拷锟斤拷锟斤拷
				T->width = T->ptr[0]->width + T->ptr[1]->width;		  //锟桔加诧拷锟斤拷锟斤拷元锟斤拷锟斤拷
				T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code); //锟斤拷锟接诧拷锟斤拷锟斤拷锟斤拷
			}
			else
			{
				T->num = T->ptr[0]->num;
				T->width = T->ptr[0]->width;
				T->code = T->ptr[0]->code;
			}
			break;
		case PARAM_DEC:
			rtn = fillSymbolTable(T->ptr[1]->type_id, newAlias(), 1, T->ptr[0]->type, 'P', T->offset);
			if (rtn == -1)
				semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "参数名重复定义");
			else
				T->ptr[1]->place = rtn;
			T->num = 1;								   //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷某锟绞硷拷?1锟�??7
			T->width = T->ptr[0]->type == INT ? 4 : 8; //锟斤拷锟斤拷锟斤拷锟斤拷
			result.kind = ID;
			strcpy(result.id, symbolTable.symbols[rtn].alias);
			result.offset = T->offset;
			T->code = genIR(PARAM, opn1, opn2, result); //锟斤拷锟缴ｏ拷FUNCTION 锟斤拷锟斤拷锟斤拷
			break;
		case COMP_STM:
			LEV++;
			//锟斤拷锟矫诧拷偶锟�??1锟�??71锟斤拷锟斤拷锟揭憋拷锟斤拷貌锟街诧拷锟斤拷锟斤拷锟节凤拷锟脚憋拷锟叫碉拷锟斤拷始位锟斤拷锟斤拷symbol_scope_TX
			symbol_scope_TX.TX[symbol_scope_TX.top++] = symbolTable.index;
			T->width = 0;
			T->code = NULL;
			if (T->ptr[0])
			{
				T->ptr[0]->offset = T->offset;
				semantic_Analysis(T->ptr[0]); //锟斤拷锟斤拷锟矫诧拷木植锟斤拷锟斤拷锟紻EF_LIST
				T->width += T->ptr[0]->width;
				T->code = T->ptr[0]->code;
			}
			if (T->ptr[1])
			{
				T->ptr[1]->offset = T->offset + T->width;
				strcpy(T->ptr[1]->Snext, T->Snext); //S.next锟斤拷锟斤拷锟斤拷锟铰达拷锟斤拷
				semantic_Analysis(T->ptr[1]);		//锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�??1锟�??7
				T->width += T->ptr[1]->width;
				T->code = merge(2, T->code, T->ptr[1]->code);
			}
#if (DEBUG)
			prn_symbol(); //c锟斤拷锟剿筹拷一锟斤拷锟斤拷锟斤拷锟斤拷锟角帮拷锟绞撅拷姆锟斤拷疟锟�??1锟�??7
						  //system("pause");
#endif
			LEV--;														   //锟斤拷锟斤拷锟斤拷锟斤拷洌拷锟脚硷拷1
			symbolTable.index = symbol_scope_TX.TX[--symbol_scope_TX.top]; //删锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟叫的凤拷锟斤拷
			break;
		case DEF_LIST:
			T->code = NULL;
			if (T->ptr[0])
			{
				T->ptr[0]->offset = T->offset;
				semantic_Analysis(T->ptr[0]); //锟斤拷锟斤拷一锟斤拷锟街诧拷锟斤拷锟斤拷锟斤拷锟斤拷
				T->code = T->ptr[0]->code;
				T->width = T->ptr[0]->width;
			}
			if (T->ptr[1])
			{
				T->ptr[1]->offset = T->offset + T->ptr[0]->width;
				semantic_Analysis(T->ptr[1]); //锟斤拷锟斤拷剩锟铰的局诧拷锟斤拷锟斤拷锟斤拷锟斤拷
				T->code = merge(2, T->code, T->ptr[1]->code);
				T->width += T->ptr[1]->width;
			}
			break;
		case VAR_DEF:
			//锟斤拷锟斤拷一锟斤拷锟街诧拷锟斤拷锟斤拷锟斤拷锟斤拷,锟斤拷锟斤拷一锟斤拷锟斤拷锟斤拷(TYPE锟斤拷锟�??1锟�??7)锟叫碉拷锟斤拷锟斤拷锟酵碉拷锟节讹拷锟斤拷锟斤拷锟接碉拷锟斤拷锟斤拷锟斤拷
			//锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷獠匡拷锟斤拷锟紼XT_VAR_DEF锟斤拷锟斤拷锟斤拷一锟街达拷锟斤拷锟斤拷锟斤拷
			T->code = NULL;
			//	T->ptr[1]->type = !strcmp(T->ptr[0]->type_id, "int") ? INT : FLOAT;  //确锟斤拷锟斤拷锟斤拷锟斤拷锟叫革拷锟斤拷锟斤拷锟斤拷锟斤拷
			if (!strcmp(T->ptr[0]->type_id, "int"))
			{
				T->ptr[1]->type = INT;
				width = 4;
			}
			if (!strcmp(T->ptr[0]->type_id, "float"))
			{
				T->ptr[1]->type = FLOAT;
				width = 4;
			}
			if (!strcmp(T->ptr[0]->type_id, "char"))
			{
				T->ptr[1]->type = CHAR;
				width = 1;
			}
			T0 = T->ptr[1]; //T0为锟斤拷锟斤拷锟斤拷锟叫憋拷锟斤拷锟斤拷锟斤拷指锟诫，锟斤拷ID锟斤拷ASSIGNOP锟斤拷锟斤拷锟节登记碉拷锟斤拷锟脚憋拷锟斤拷锟斤拷为锟街诧拷锟斤拷锟斤拷
			num = 0;
			T0->offset = T->offset;
			T->width = 0;
			width = T->ptr[1]->type == INT ? 4 : 8; //一锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
			while (T0)
			{
				//锟斤拷锟斤拷锟斤拷锟斤拷DEC_LIST锟斤拷锟�??1锟�??7
				num++;
				T0->ptr[0]->type = T0->type; //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟铰达拷锟斤拷
				if (T0->ptr[1])
					T0->ptr[1]->type = T0->type;
				T0->ptr[0]->offset = T0->offset; //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟铰达拷锟斤拷
				if (T0->ptr[1])
					T0->ptr[1]->offset = T0->offset + width;
				if (T0->ptr[0]->kind == ID)
				{
					rtn = fillSymbolTable(T0->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width); //锟剿达拷偏锟斤拷锟斤拷未锟斤拷锟姐，锟斤拷时为0
					if (rtn == -1)
						semantic_error(T0->ptr[0]->pos, T0->ptr[0]->type_id, "变量重复定义");
					else
						T0->ptr[0]->place = rtn;
					T->width += width;
				}
				else if (T0->ptr[0]->kind == ASSIGNOP)
				{
					rtn = fillSymbolTable(T0->ptr[0]->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width); //锟剿达拷偏锟斤拷锟斤拷未锟斤拷锟姐，锟斤拷时为0
					if (rtn == -1)
						semantic_error(T0->ptr[0]->ptr[0]->pos, T0->ptr[0]->ptr[0]->type_id, "变量重复定义");
					else
					{
						T0->ptr[0]->place = rtn;
						T0->ptr[0]->ptr[1]->offset = T->offset + T->width + width;
						Exp(T0->ptr[0]->ptr[1]);
						opn1.kind = ID;
						strcpy(opn1.id, symbolTable.symbols[T0->ptr[0]->ptr[1]->place].alias);
						result.kind = ID;
						strcpy(result.id, symbolTable.symbols[T0->ptr[0]->place].alias);
						T->code = merge(3, T->code, T0->ptr[0]->ptr[1]->code, genIR(ASSIGNOP, opn1, opn2, result));
					}
					T->width += width + T0->ptr[0]->ptr[1]->width;
				}
				else if (T0->ptr[0]->kind == ARRAY_DF)
				{
					rtn = fillSymbolTable(T0->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'A', T->offset + T->width);
					if (rtn == -1)
						semantic_error(T0->ptr[0]->pos, T0->ptr[0]->type_id, "变量重复定义");
					else
					{
						T0->ptr[0]->place = rtn;
						if (fillArray(T0->ptr[0]->ptr[0], symbolTable.symbols[T0->ptr[0]->place].array, 0) == -1)
						{
							semantic_error(T0->ptr[0]->pos, T0->ptr[0]->type_id, "数组维度过大");
							break;
						}
					}
					T->width += width * calArrayNums(T0->ptr[0]->ptr[0]);
				}
				T0 = T0->ptr[1];
			}
			break;
		case STM_LIST:
			if (!T->ptr[0])
			{
				T->code = NULL;
				T->width = 0;
				break;
			}			   //锟斤拷锟斤拷锟斤拷锟斤拷锟�??1锟�??7
			if (T->ptr[1]) //2锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷樱锟斤拷锟斤拷锟斤拷卤锟斤拷锟斤拷为锟斤拷一锟斤拷锟斤拷锟斤拷锟斤拷锟襟到达拷锟轿伙拷锟�??1锟�??7
				strcpy(T->ptr[0]->Snext, newLabel());
			else //锟斤拷锟斤拷锟斤拷薪锟斤拷锟揭伙拷锟斤拷锟戒，S.next锟斤拷锟斤拷锟斤拷锟铰达拷锟斤拷
				strcpy(T->ptr[0]->Snext, T->Snext);
			T->ptr[0]->offset = T->offset;
			semantic_Analysis(T->ptr[0]);
			T->code = T->ptr[0]->code;
			T->width = T->ptr[0]->width;
			if (T->ptr[1])
			{ //2锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�??1锟�??7,S.next锟斤拷锟斤拷锟斤拷锟铰达拷锟斤拷
				strcpy(T->ptr[1]->Snext, T->Snext);
				T->ptr[1]->offset = T->offset; //顺锟斤拷峁癸拷锟斤拷锟斤拷锟皆拷锟斤拷?1锟�??7
											   //                  T->ptr[1]->offset=T->offset+T->ptr[0]->width; //顺锟斤拷峁顾筹拷锟斤拷锟戒单元锟斤拷式
				semantic_Analysis(T->ptr[1]);
				//锟斤拷锟斤拷锟叫碉拷1锟斤拷为锟斤拷锟斤拷式锟斤拷洌拷锟斤拷锟斤拷锟戒，锟斤拷锟斤拷锟斤拷锟绞憋拷锟斤拷锟�??1锟�??72锟斤拷前锟斤拷锟斤拷要锟斤拷锟�??1锟�??7
				if (T->ptr[0]->kind == RETURN || T->ptr[0]->kind == EXP_STMT || T->ptr[0]->kind == COMP_STM)
					T->code = merge(2, T->code, T->ptr[1]->code);
				else
					T->code = merge(3, T->code, genLabel(T->ptr[0]->Snext), T->ptr[1]->code);
				if (T->ptr[1]->width > T->width)
					T->width = T->ptr[1]->width; //顺锟斤拷峁癸拷锟斤拷锟斤拷锟皆拷锟斤拷?1锟�??7
												 //                        T->width+=T->ptr[1]->width;//顺锟斤拷峁顾筹拷锟斤拷锟戒单元锟斤拷式
			}
			break;
		case IF_THEN:
			strcpy(T->ptr[0]->Etrue, newLabel()); //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷转锟斤拷位锟斤拷
			strcpy(T->ptr[0]->Efalse, T->Snext);
			T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
			boolExp(T->ptr[0]);
			T->width = T->ptr[0]->width;
			strcpy(T->ptr[1]->Snext, T->Snext);
			semantic_Analysis(T->ptr[1]); //if锟接撅拷
			if (T->width < T->ptr[1]->width)
				T->width = T->ptr[1]->width;
			T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code);
			break; //锟斤拷锟斤拷锟斤拷涠硷拷锟矫伙拷写锟斤拷锟給ffset锟斤拷width锟斤拷锟斤拷
		case IF_THEN_ELSE:
			strcpy(T->ptr[0]->Etrue, newLabel()); //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷转锟斤拷位锟斤拷
			strcpy(T->ptr[0]->Efalse, newLabel());
			T->ptr[0]->offset = T->ptr[1]->offset = T->ptr[2]->offset = T->offset;
			boolExp(T->ptr[0]); //锟斤拷锟斤拷锟斤拷要锟斤拷锟斤拷锟斤拷锟斤拷路锟斤拷锟诫处锟斤拷
			T->width = T->ptr[0]->width;
			strcpy(T->ptr[1]->Snext, T->Snext);
			semantic_Analysis(T->ptr[1]); //if锟接撅拷
			if (T->width < T->ptr[1]->width)
				T->width = T->ptr[1]->width;
			strcpy(T->ptr[2]->Snext, T->Snext);
			semantic_Analysis(T->ptr[2]); //else锟接撅拷
			if (T->width < T->ptr[2]->width)
				T->width = T->ptr[2]->width;
			T->code = merge(6, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code,
							genGoto(T->Snext), genLabel(T->ptr[0]->Efalse), T->ptr[2]->code);
			break;
		case WHILE:

			strcpy(T->ptr[0]->Etrue, newLabel()); //锟接斤拷锟教筹拷锟斤拷锟皆的硷拷锟斤拷
			strcpy(T->ptr[0]->Efalse, T->Snext);
			T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
			boolExp(T->ptr[0]); //循锟斤拷锟斤拷锟斤拷锟斤拷要锟斤拷锟斤拷锟斤拷锟斤拷路锟斤拷锟诫处锟斤拷
			T->width = T->ptr[0]->width;
			strcpy(T->ptr[1]->Snext, newLabel());

			flag++; //锟睫改筹拷+1锟斤拷锟斤拷锟狡诧拷锟斤拷

			breakTable.breaks[breakTable.index++] = genGoto(T->Snext);
			continueTable.continues[continueTable.index++] = genGoto(T->ptr[1]->Snext);

			semantic_Analysis(T->ptr[1]); //循锟斤拷锟斤拷
			if (T->width < T->ptr[1]->width)
				T->width = T->ptr[1]->width;
			T->code = merge(5, genLabel(T->ptr[1]->Snext), T->ptr[0]->code,
							genLabel(T->ptr[0]->Etrue), T->ptr[1]->code, genGoto(T->ptr[1]->Snext));

			flag--;
			breakTable.breaks[--breakTable.index] = NULL;
			continueTable.continues[--continueTable.index] = NULL;

			break;
		case EXP_STMT:
			T->ptr[0]->offset = T->offset;
			semantic_Analysis(T->ptr[0]);
			T->code = T->ptr[0]->code;
			T->width = T->ptr[0]->width;
			break;
		case RETURN:
			if (T->ptr[0])
			{
				T->ptr[0]->offset = T->offset;
				Exp(T->ptr[0]);
				num = symbolTable.index;
				do
					num--;
				while (symbolTable.symbols[num].flag != 'F');
				if (T->ptr[0]->type != symbolTable.symbols[num].type)
				{
					semantic_error(T->pos, "返回值类型错误，语义错误", "");
					T->width = 0;
					T->code = NULL;
					return;
				}
				/*锟斤拷要锟叫断凤拷锟斤拷值锟斤拷锟斤拷锟角凤拷匹锟斤拷*/

				T->width = T->ptr[0]->width;
				result.kind = ID;
				strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
				result.offset = symbolTable.symbols[T->ptr[0]->place].offset;
				T->code = merge(2, T->ptr[0]->code, genIR(RETURN, opn1, opn2, result));
			}
			else
			{
				T->width = 0;
				result.kind = 0;
				T->code = genIR(RETURN, opn1, opn2, result);
			}
			break;

		case FOR_NODE:
			LEV++;

			T->ptr[0]->offset = T->offset;
			symbol_scope_TX.TX[symbol_scope_TX.top++] = symbolTable.index;
			semantic_Analysis(T->ptr[0]); //循锟斤拷锟斤拷始锟斤拷锟�??1锟�??7
			T->ptr[2]->offset = T->offset + T->ptr[0]->width;
			semantic_Analysis(T->ptr[2]);
			strcpy(T->ptr[1]->Etrue, newLabel()); //锟接斤拷锟教筹拷锟斤拷锟皆的硷拷锟斤拷
			strcpy(T->ptr[1]->Efalse, T->Snext);
			T->ptr[1]->offset = T->ptr[2]->offset + T->ptr[2]->width;
			boolExp(T->ptr[1]); //循锟斤拷锟斤拷锟斤拷
			T->width = T->ptr[0]->width + T->ptr[1]->width + T->ptr[2]->width;
			T->ptr[3]->offset = T->ptr[2]->offset + T->ptr[2]->width;
			strcpy(T->ptr[3]->Snext, newLabel());
			flag++;
			semantic_Analysis(T->ptr[1]);

			breakTable.breaks[breakTable.index++] = genGoto(T->Snext);
			continueTable.continues[continueTable.index++] = genGoto(T->ptr[3]->Snext);

			semantic_Analysis(T->ptr[3]); //循锟斤拷锟斤拷
			if (T->width < T->ptr[3]->width)
				T->width = T->ptr[3]->width;
			T->code = merge(7, T->ptr[0]->code,
							T->ptr[1]->code, genLabel(T->ptr[3]->Snext), T->ptr[2]->code,
							genLabel(T->ptr[1]->Etrue), T->ptr[3]->code, genGoto(T->ptr[3]->Snext));

			flag--;
			LEV--;
			breakTable.breaks[--breakTable.index] = NULL;
			continueTable.continues[--continueTable.index] = NULL;
			break;
		/*case FOR_DEC:
			semantic_Analysis(T->ptr[0]);  //循锟斤拷锟斤拷始锟斤拷锟�??1锟�??7
			semantic_Analysis(T->ptr[1]);  //循锟斤拷锟斤拷锟斤拷
			semantic_Analysis(T->ptr[2]);  //循锟斤拷锟戒换锟斤拷锟斤拷式
			break;
		case FOR_EXP1:
			Exp(T->ptr[0]);
			Exp(T->ptr[1]);
			break;
		case FOR_EXP2:
			T0 = T;
			while (T0) {
				boolExp(T0->ptr[0]);
				T0 = T0->ptr[1];
			}
			boolExp(T->ptr[0]);
			break;
		case FOR_EXP3:
			T0 = T;
			while (T0) {
				semantic_Analysis(T0->ptr[0]);
				T0 = T0->ptr[1];
			}
			break;*/
		case BREAK_NODE:
			if (flag == 0)
				semantic_error(T->pos, " ", "break语句出现位置错误");
			T->code = breakTable.breaks[breakTable.index - 1];
			break;
		case CONTINUE_NODE:
			if (flag == 0)
				semantic_error(T->pos, " ", "continue语句出现位置错误");
			T->code = continueTable.continues[continueTable.index - 1];
			break;

		case ID:
		case INT:
		case FLOAT:
		case CHAR:
		case ARRAY_DF:
		case ASSIGNOP:
		case AND:
		case OR:
		case RELOP:
		case PLUS:
		case MINUS:
		case STAR:
		case DIV:
		case COMADD:
		case COMSUB:
		case COMDIV:
		case COMSTAR:
		case COMMOD:
		case AUTOADD:
		case AUTOSUB:
		case NOT:
		case UMINUS:
		case FUNC_CALL:
		case ARRAY_CALL:
		case ARGS:
			Exp(T); //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷式
			break;
		}
	}
}

void semantic_Analysis0(struct ASTNode *T)
{
	symbolTable.index = 0;
	breakTable.index = 0;
	continueTable.index = 0;
	fillSymbolTable("read", "", 0, INT, 'F', 4);
	symbolTable.symbols[0].paramnum = 0; //read锟斤拷锟轿参革拷锟斤拷
	fillSymbolTable("write", "", 0, INT, 'F', 4);
	symbolTable.symbols[1].paramnum = 1;
	fillSymbolTable("x", "", 1, INT, 'P', 12);
	symbol_scope_TX.TX[0] = 0; //锟解部锟斤拷锟斤拷锟节凤拷锟脚憋拷锟叫碉拷锟斤拷始锟斤拷锟斤拷?1锟�??70
	symbol_scope_TX.top = 1;
	T->offset = 0; //锟解部锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷偏锟斤拷锟斤拷
	semantic_Analysis(T);
	T->code = splitBlock(T->code);
	prnIR(T->code);
	optimize_main(); //进行简单的代码优化
					 //objectCode(T->code);
}

void callArray(struct ASTNode *T)
{
	if (T)
	{
		switch (T->kind)
		{
		case INT:
			if (T->type_int <= 0)
			{
				semantic_error(T->pos, "", "数组下标不能为负值或0");
				break;
			}
			break;
		case FLOAT:
		case CHAR:
			semantic_error(T->pos, "", "数组下标表达式非法");
			break;
		case ARRAY_CALL:
			Exp(T->ptr[0]);
			Exp(T->ptr[1]);
			callArray(T->ptr[0]);
			callArray(T->ptr[1]);
			break;
		default:
			break;
		}
	}
}

/**
 * 计算数组的元素个数
 * @return: 数组元素个数
 */
int calArrayNums(struct ASTNode *T)
{
	if (T)
	{
		if (T->type == INT)
		{
			return T->type_int;
		}
		return T->ptr[0]->type_int * calArrayNums(T->ptr[1]);
	}
	else
		return 1;
}

/**
 * 填充数组的维度
 */
int fillArray(struct ASTNode *T, int *array, int index)
{
	if (index == ARRAY_LEN)
		return -1;
	if (T->type == INT)
	{
		array[index] = T->type_int;
		return 1;
	}
	else
	{
		array[index] = T->ptr[0]->type_int;
		return fillArray(T->ptr[1], array, index + 1);
	}
}

//计算数组每一维度的宽度
int calArrayPerWidth(int *array, int index)
{
	int res = 1;
	while (array[index] != 0 && index < ARRAY_LEN)
	{
		res *= array[index];
		index++;
	}
	return res;
}

//计算数组所有维度的宽度
int calArrayWidth(struct ASTNode *T, int *array, int index)
{
	if (T->type == INT)
	{
		return T->type_int;
	}
	if (T->ptr[0])
		return (T->ptr[0]->type_int) * calArrayPerWidth(array, index + 1) + calArrayWidth(T->ptr[1], array, index + 1);
	else
	{
		return 1;
	}
}

void objectCode(struct codenode *head)
{
	char opnstr1[32], opnstr2[32], resultstr[32];
	struct codenode *h = head, *p;
	int i;
	FILE *fp;
	fp = fopen("object.s", "w");
	fprintf(fp, ".data\n");
	fprintf(fp, "_Prompt: .asciiz \"Enter an integer:  \"\n");
	fprintf(fp, "_ret: .asciiz \"\\n\"\n");
	fprintf(fp, ".globl main\n");
	fprintf(fp, ".text\n");
	fprintf(fp, "read:\n");
	fprintf(fp, "  li $v0,4\n");
	fprintf(fp, "  la $a0,_Prompt\n");
	fprintf(fp, "  syscall\n");
	fprintf(fp, "  li $v0,5\n");
	fprintf(fp, "  syscall\n");
	fprintf(fp, "  jr $ra\n");
	fprintf(fp, "write:\n");
	fprintf(fp, "  li $v0,1\n");
	fprintf(fp, "  syscall\n");
	fprintf(fp, "  li $v0,4\n");
	fprintf(fp, "  la $a0,_ret\n");
	fprintf(fp, "  syscall\n");
	fprintf(fp, "  move $v0,$0\n");
	fprintf(fp, "  jr $ra\n");
	do
	{
		switch (h->op)
		{
		case ASSIGNOP:
			if (h->opn1.kind == INT)
				fprintf(fp, "  li $t3, %d\n", h->opn1.const_int);
			else
			{
				fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
				fprintf(fp, "  move $t3, $t1\n");
			}
			fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
			break;
		case PLUS:
		case MINUS:
		case STAR:
		case DIV:
			fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
			fprintf(fp, "  lw $t2, %d($sp)\n", h->opn2.offset);
			if (h->op == PLUS)
				fprintf(fp, "  add $t3,$t1,$t2\n");
			else if (h->op == MINUS)
				fprintf(fp, "  sub $t3,$t1,$t2\n");
			else if (h->op == STAR)
				fprintf(fp, "  mul $t3,$t1,$t2\n");
			else if(h->op == DIV)
			{
				fprintf(fp, "  div $t1, $t2\n");
				fprintf(fp, "  mflo $t3\n");
			}
			fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
			break;
		case FUNCTION:
			fprintf(fp, "\n%s:\n", h->result.id);
			if (!strcmp(h->result.id, "main"))
				fprintf(fp, "  addi $sp, $sp, -%d\n", symbolTable.symbols[h->result.offset].offset);
			break;
		case PARAM:
			break;
		case LABEL:
			fprintf(fp, "%s:\n", h->result.id);
			break;
		case GOTO:
			fprintf(fp, "  j %s\n", h->result.id);
			break;
		case JLE:
		case JLT:
		case JGE:
		case JGT:
		case EQ:
		case NEQ:
			fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
			fprintf(fp, "  lw $t2, %d($sp)\n", h->opn2.offset);
			if (h->op == JLE)
				fprintf(fp, "  ble $t1,$t2,%s\n", h->result.id);
			else if (h->op == JLT)
				fprintf(fp, "  blt $t1,$t2,%s\n", h->result.id);
			else if (h->op == JGE)
				fprintf(fp, "  bge $t1,$t2,%s\n", h->result.id);
			else if (h->op == JGT)
				fprintf(fp, "  bgt $t1,$t2,%s\n", h->result.id);
			else if (h->op == EQ)
				fprintf(fp, "  beq $t1,$t2,%s\n", h->result.id);
			else
				fprintf(fp, "  bne $t1,$t2,%s\n", h->result.id);
			break;
		case ARG:
			break;
		case CALL:
			if (!strcmp(h->opn1.id, "read"))
			{
				fprintf(fp, "  addi $sp, $sp, -4\n");
				fprintf(fp, "  sw $ra,0($sp)\n");
				fprintf(fp, "  jal read\n");
				fprintf(fp, "  lw $ra,0($sp)\n");
				fprintf(fp, "  addi $sp, $sp, 4\n");
				fprintf(fp, "  sw $v0, %d($sp)\n", h->result.offset);
				break;
			}
			if (!strcmp(h->opn1.id, "write"))
			{
				fprintf(fp, "  lw $a0, %d($sp)\n", h->prior->result.offset);
				fprintf(fp, "  addi $sp, $sp, -4\n");
				fprintf(fp, "  sw $ra,0($sp)\n");
				fprintf(fp, "  jal write\n");
				fprintf(fp, "  lw $ra,0($sp)\n");
				fprintf(fp, "  addi $sp, $sp, 4\n");
				break;
			}

			for (p = h, i = 0; i < symbolTable.symbols[h->opn1.offset].paramnum; i++)
				p = p->prior;

			fprintf(fp, "  move $t0,$sp\n");
			fprintf(fp, "  addi $sp, $sp, -%d\n", symbolTable.symbols[h->opn1.offset].offset);
			fprintf(fp, "  sw $ra,0($sp)\n");
			i = h->opn1.offset + 1;
			while (symbolTable.symbols[i].flag == 'P')
			{
				fprintf(fp, "  lw $t1, %d($t0)\n", p->result.offset);
				fprintf(fp, "  move $t3,$t1\n");
				fprintf(fp, "  sw $t3,%d($sp)\n", symbolTable.symbols[i].offset);
				p = p->next;
				i++;
			}
			fprintf(fp, "  jal %s\n", h->opn1.id);
			fprintf(fp, "  lw $ra,0($sp)\n");
			fprintf(fp, "  addi $sp,$sp,%d\n", symbolTable.symbols[h->opn1.offset].offset);
			fprintf(fp, "  sw $v0,%d($sp)\n", h->result.offset);
			break;
		case RETURN:
			fprintf(fp, "  lw $v0,%d($sp)\n", h->result.offset);
			fprintf(fp, "  jr $ra\n");
			break;
		case BLOCK:
			break;
		}
		h = h->next;
	} while (h != head);
	fclose(fp);
}
