#include "def.h"

#define INTEGER_MINVALUE -2147483648

char tokens[20][20]; //用来存储TAC语句信息
const char spState[8][20] = {"FUNCTION", "GOTO", "CALL", "PARAM", "LABEL", "ARG", "RETURN","BLOCK"};

int varlen = 0; //记录当前变量长度
int lineNo = 0; //记录行号

//寻找变量的位置
int find(char *s)
{
	int i;
	for (i = 0; i < varlen; i++)
	{
		if (strcmp(var[i].label, s) == 0)
			return i;
	}
	return -1;
}

//给出剔除掉无用代码的结果
void getLiveCode(FILE *f, FILE *g)
{
	int i, j, k = 0, n;
	int rmlines[1024];
	char tac[50];
	for (i = 0; i < varlen; i++)
	{
		if (var[i].flag == 0)
			for (j = 0; j < var[i].nlines; j++)
				rmlines[k++] = var[i].line[j]; //记录变量行
	}
	n = k;
	k = 1;
	while (fgets(tac, 50, f))
	{
		for (i = 0; i < n; i++)
		{
			if (rmlines[i] == k)
				break;
		}
		if (i == n)
		{
			//printf("%s", tac);
			fputs(tac, g);
		}
		k++;
	}
}

int isBeginWith(const char *str1, char *str2)
{
	if (str1 == NULL || str2 == NULL)
		return -1;
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	if ((len1 > len2) || (len1 == 0 || len2 == 0))
		return -1;
	char *p = str2;
	int i = 0;
	while (i < len1)
	{
		if (*p != str1[i])
			return 0;
		p++;
		i++;
	}
	return 1;
}

int isSPStatement(char *str)
{
	if (isBeginWith("IF", str) == 1)
		return 1;
	else
	{
		int len = strlen(spState);
		for (int i = 0; i < len; ++i)
		{
			if (isBeginWith(spState[i], str) == 1)
				return 2;
		}
	}
	return 0;
}

int containsLBRB(char * str){
	if(str == NULL)
		return -1;
	int len = strlen(str);
	for(int i = 0 ; i < len ; ++i){
		if(str[i] == '[' || str[i] == ']')
			return 1;
	}
	return 0;
}

//删除部分无用代码
void deadCode(int l)
{
	lineNo++; //行号递增
	int n, m, j;
	int state = isSPStatement(tokens[0]);
	if (state == 1)
	{
		j = find(tokens[1]);
		m = atoi(tokens[3]);
		n = find(tokens[5]);
	}
	else if (state == 2)
	{
		j = find(tokens[1]);
		m = -1;
		n = -1;
	}
	else
	{
		n = atoi(tokens[4]); //将操作数整形化
		m = atoi(tokens[2]);
		j = find(tokens[0]); //寻找目标变量结果的位置
	}
	if(containsLBRB(tokens[0]))
		return;
	if(l == 5 && isBeginWith("BLOCK",tokens[0]) == 0 && isBeginWith("LABEL",tokens[0]) == 0){
		//特殊情况 temp = call func \n
		if(j == -1){
			strcpy(var[varlen].label, tokens[0]);
			var[varlen].flag = 1;
			var[varlen].line[0] = lineNo;
			var[varlen].nlines = 1;
			varlen++;
		}else{
			var[j].flag = 1;
		}
		return;
	}
	if (varlen == 0 || j == -1) //写入新变量
	{
		if (state == 2 || state == 1){
			strcpy(var[varlen].label, tokens[1]);
			var[varlen].flag = 1;
		}
		else{
			strcpy(var[varlen].label, tokens[0]);
			var[varlen].flag = 0;
		}
		var[varlen].line[0] = lineNo;
		var[varlen].nlines = 1;
		varlen++;
	}
	else if (j > -1) //tokens[0] 也是变量
	{
		if (state == 2 || state == 1){
			var[j].flag = 1;
		}
		if (var[j].flag == 0)
		{
			var[j].line[var[j].nlines] = lineNo;
			var[j].nlines++;
		}
	}
	if (m == 0) //说明是变量
	{
		if (state == 1)
			j = find(tokens[3]);
		else
			j = find(tokens[2]);
		if (j > -1)
		{
			if (state == 2 || state == 1 || var[j].nlines == 1) //出现了，将flag置1
				var[j].flag = 1;
				else{
					var[j].nlines--;
					var[j].flag = 0;
				}
		}
	}
	if (n == 0 && strcmp(tokens[4], "0") && l > 3) //说明最后一个操作数是变量
	{
		if (state == 1)
			j = find(tokens[5]);
		else
			j = find(tokens[4]);
		if (j > -1)
		{
			if (state == 2 || state == 1 || var[j].nlines == 1) //出现了，将flag置1
				var[j].flag = 1;
				else{
					var[j].nlines--;
					var[j].flag = 0;
				}
		}
	}
}

//对中间代码进行简单的运算优化
void optimize(int l,hash * head,FILE * f)
{
	int n, m, i, j;
	float flo;
	if (l < 5)
	{
		for (i = 0; i < l; i++){
			j = strlen(tokens[i]);
			if(tokens[i][j-1] == '\n')
				tokens[i][j-1] = '\0';
			n = getValue(head,tokens[i]);
			if(n == INTEGER_MINVALUE){
				//printf("%s ", tokens[i]);
				fprintf(f,"%s ", tokens[i]);
			}
			else
			{
				//printf("%d ",n);
				fprintf(f,"%d ",n);
			}
		}
		return;
	}
	int state = isSPStatement(tokens[0]);
	char * tmp_1;
	char * tmp_2;
	if(state == 0){
		tmp_1 = tokens[2];
		tmp_2 = tokens[4];
	}else if(state == 1){
		tmp_1 = tokens[1];
		tmp_2 = tokens[3];
	}else {
		tmp_1 = tokens[1];
		tmp_2 = NULL;
	}

	m = atoi(tmp_1);
	n = atoi(tmp_2);
	if(n == 0 && tmp_2 != NULL && strcmp(tmp_2, "0")){
		j = getValue(head,tmp_2);
		if(j != INTEGER_MINVALUE)
			n = j;
	}
	if(m == 0 && tmp_1 != NULL && strcmp(tmp_1, "0")){
		j = getValue(head,tmp_1);
		if(j != INTEGER_MINVALUE)
			m = j;
	}
	if (m != 0 && n != 0)
	{
		if (strcmp(tokens[3], "+") == 0)
			fprintf(f,"%s = %d", tokens[0], m + n);
		if (strcmp(tokens[3], "*") == 0)
			fprintf(f,"%s = %d", tokens[0], m * n);
		if (strcmp(tokens[3], "/") == 0)
			fprintf(f,"%s = %d", tokens[0], m / n);
		if (strcmp(tokens[3], "-") == 0)
			fprintf(f,"%s = %d", tokens[0], m - n);
	}else if (strcmp(tokens[3], "*") == 0 && strcmp(tokens[4], "1\n") == 0)
		fprintf(f,"%s = %s", tokens[0], tokens[2]);
	else if (strcmp(tokens[3], "+") == 0 && strcmp(tokens[4], "0\n") == 0)
		fprintf(f,"%s = %s", tokens[0], tokens[2]);
	else if (strcmp(tokens[3], "*") == 0 && tmp_2[0] <= '9' && ceilf(flo = log2(n)) == flo)
		fprintf(f,"%s = %s << %d", tokens[0], tokens[2], (int)flo);
	else if (strcmp(tokens[3], "/") == 0 && tmp_2[0] <= '9' && ceilf(flo = log2(n)) == flo)
		fprintf(f,"%s = %s >> %d", tokens[0], tokens[2], (int)flo);
	else{
		for (i = 0; i < l; i++){
			j = strlen(tokens[i]);
			if(tokens[i][j-1] == '\n')
				tokens[i][j-1] = '\0';
			n = getValue(head,tokens[i]);
			if(n == INTEGER_MINVALUE)
				fprintf(f,"%s ", tokens[i]);
			else
			{
				fprintf(f,"%d ",n);
			}
		}
	}
}

//逐行读入TAC语句，返回值为tokens数组的空闲位置
int tokenize(char *str)
{
	int i = 0;
	char *s = strtok(str, " "); //按空格分割字符串
	while (s != NULL)
	{

		strcpy(tokens[i++], s);
		s = strtok(NULL, " ");
	}
	return i;
}

hash * insert(hash * head , char * key ,int val){
	hash * p = (hash *)malloc(sizeof(hash));
	strcpy(p->label,key);
	p->val = val;
	p->next = head;
	head = p;
	return head;
}

int getValue(hash * head,char * key){
	hash * p = head;
	while (p->val != INTEGER_MINVALUE &&  p != NULL)
	{
		if(!strcmp(p->label,key))
			return p->val;
		else
			p = p->next;
	}
	return INTEGER_MINVALUE;
}

int optimize_main()
{
	//printf("----------------------");
	//printf("start optimize inner code\n");
	FILE * f = fopen("code.txt","r");
	FILE * g = fopen("optimized.txt","w+");
	int l;
	char tac[50];
	hash * head = (hash *)malloc(sizeof(hash));
	head->next = NULL;
	head->val = INTEGER_MINVALUE;
	//首先记录临时变量的值
	while ((fgets(tac,50,f)))
	{
		l = tokenize(tac);
		if(l == 3 && isBeginWith("temp",&tokens[0]) == 1){
			int n = atoi(tokens[2]);
			if(n == 0 && strcmp(tokens[2],"0\n") != 0)
				n = tokens[2][0];
			head = insert(head,tokens[0],n);
		}
	}
	fclose(f);
	//接着输出算数优化后的代码
	f = fopen("code.txt","r");
	while ((fgets(tac,50,f)))
	{
		l = tokenize(tac);
		if(l == 3 && isBeginWith("temp",tokens[0]) == 1)
			continue;
		optimize(l,head,g);
		fprintf(g,"\n");
	}
	fclose(f);
	fclose(g);
	//最后剔除无用代码
	f = fopen("optimized.txt","r");
	g = fopen("temp.txt","w+");
	while (fgets(tac,50,f))
	{
		//由于前面经历了一次optimize，所以这里的l会比原本多1
		l = tokenize(tac);
		deadCode(l);
	}
	fclose(f);
	f = fopen("optimized.txt","r");
	getLiveCode(f,g);
	fclose(f);
	fclose(g);
	f = fopen("temp.txt","r");
	g = fopen("optimized.txt","w+");
	//最后在进行一次算数优化
	while ((fgets(tac,50,f)))
	{
		l = tokenize(tac);
		optimize(l,head,g);
		fprintf(g,"\n");
	}
	fclose(f);
	fclose(g);

}
