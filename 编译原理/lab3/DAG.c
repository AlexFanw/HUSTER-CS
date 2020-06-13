#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global variables
int numBasicBlocks = 0;
int cfgEdges[100][100];
int cfgNodes[100];

//structure for each leader
struct l
{
	int line, flag; //use flag variable to check if each leader is entered in the CFG
	char instr[50], leadkey[25], gotokey[25]; //leadkey and gotokey are the labels for each leader (beginning and end)
	struct l *next, *prev; //next and prev leader pointers
};
typedef struct l *LEAD;

//structure for each basic block
struct b
{
	LEAD leader; //leader of the block
	char gotokey[25], leadkey[25]; //beginning and ending labels for each block
	int start, end; //line numbers
	struct b *next[2], *prev[2]; //next and prev basic block pointers
};
typedef struct b *BASIC; 

LEAD firstLeader;
BASIC firstBlock;

//returns a leader variable pointer
LEAD getLeader()
{
	LEAD x = (LEAD)malloc(sizeof(struct l));
	if(x == NULL)
	{
		printf("\n Insufficient memory. ");
		exit(0);
	}
	x->next = x->prev = NULL;
	return x;
}

//returns a basic block variable pointer
BASIC getBasicBlock()
{
	BASIC b = (BASIC)malloc(sizeof(struct b));
	if(b == NULL)
	{
		printf("\n Insufficient memory. ");
		exit(0);
	}
	int i;
	for(i=0; i<2; i++)
		b->next[i] = b->prev[i] = NULL;
	return b;
}

//returns the basic block with the given leadkey/starting label
BASIC FindBlock(BASIC initialBlock, LEAD prevLead)
{
	BASIC tn = firstBlock;
	while(tn != NULL)
	{
		if((strcmp(tn->gotokey, prevLead->gotokey) == 0) && (strcmp(tn->leadkey, prevLead->leadkey))==0)
			return tn;
		else
			tn = tn->next[0];
	}
}


//insert rear for each leader 
//gives a linked list of all the leaders
LEAD insertLead(LEAD initial, LEAD newLeader)
{
	if(initial == NULL)
	{
		newLeader->prev = NULL;
		initial = newLeader;
		return initial;
	}
	LEAD tn, pn;
	tn = initial;
	while(tn!=NULL)
	{
		pn = tn;
		tn = tn->next;
	}
	pn->next = newLeader;
	newLeader->prev = pn;
	return initial;
}

//insert the Basic block to the tree/graph structure
BASIC insertBasic(BASIC initial, BASIC newBasic, int flag, LEAD prevLead)
{
	if(initial == NULL)
	{
		newBasic->prev[0] = NULL;
		initial = newBasic;
		return initial;
	}
	BASIC tn, pn;
	LEAD tempLead = firstLeader, oldLead;
	tn = initial;
	if(flag == 0)
	{
		while(tn!=NULL)
		{
			pn = tn;
			tn = tn->next[0];
		}
		pn->next[0] = newBasic;
		newBasic->prev[0] = pn;
	}
	else
	{
		while((tempLead != NULL) && ((strcmp(tempLead->leadkey, prevLead->leadkey)!=0) || (strcmp(tempLead->gotokey, prevLead->gotokey)!=0)))
		{
			oldLead = tempLead;
			tempLead = tempLead->next;
		}
		tn = FindBlock(initial, oldLead);
		if(tn != NULL)
			tn->next[1] = newBasic;
		newBasic->prev[0] = tn;
	}
	return initial;
}

//string matching function used to check for 'goto' keys in an instruction
int StringMatch(char string[], char cmpstring[], char keystring[])
{
	int i,j, k;
	int match;

	for(i=0; string[i]!='\0'; i++)
	{
		for(j=0; cmpstring[j]!='\0'; j++)
		{
			if(string[i+j] != cmpstring[j])
			{
				j++;
				break;
			}
		}
		if(cmpstring[j] == '\0')
		{
			i += j;
			i++;
			k = 0;
			for(k; string[i] != '\n'; i++)
				keystring[k++] = string[i];
			keystring[k] = '\0';
			return 1;
		}
	}
	return 0;
}

//print the list of basic blocks
void printBasic(BASIC first)
{
	if(first == NULL)
	{
		printf("\n The basic block list is empty. ");
		return;
	}
	else
	{
		BASIC temp;
		temp = first;
		while(temp != NULL)
		{
			printf("\n Block :  startkey %s , end %s", temp->leadkey, temp->gotokey);
			temp = temp->next[0];
		}
	}
}

//print the list of leaders
void printLeader(LEAD first)
{
	numBasicBlocks = 0;
	if(first == NULL)
	{
		printf("\n The Leader list is empty. ");
		return;
	}
	else
	{
		LEAD temp;
		temp = first;
		while(temp != NULL)
		{
			++numBasicBlocks;
			printf("\n Leader : line %d, startkey = %s, endkey = %s", temp->line, temp->leadkey, temp->gotokey);
			temp = temp->next;
		}
	}
}

//get the leadkey/starting label (if any) of an instruction
void getStartkey(char Instr[50], char key[25])
{
	int i;
	for(i=0; Instr[i]!=':'; i++)
		key[i] = Instr[i];
	key[i] = '\0';
}

//returns the leaders with the given starting label/leadkey
LEAD Find(char startkey[], LEAD curLead)
{
	LEAD tn = firstLeader;
	while((strcmp(startkey, tn->leadkey) != 0) && (tn!=NULL))
		tn =tn->next;
	return tn;
}

int isBackJump(LEAD prevLead, LEAD curLead, LEAD initialLead)
{
	LEAD tn = prevLead;
	while(tn != curLead && tn != NULL)
		tn = tn->next;
	if(tn == curLead)
		return 0;
	if(tn == NULL)
		return 1;
}

//returns list of all basic blocks
BASIC getBasicBlockList(BASIC initialBlock, LEAD initialLead, int flag)
{
	int loopflag = 0, condState;
	BASIC curBlock, prevBlock;
	LEAD curLead, nextLead, prevLead, loopKey;
	nextLead = initialLead;
//	curBlock = initialBlock;

	if(initialBlock == NULL)
	{
		initialBlock = getBasicBlock();
		initialBlock->leader = nextLead;
		initialBlock->leader->flag = 1;
		strcpy(initialBlock->leadkey, nextLead->leadkey);
		strcpy(initialBlock->gotokey, nextLead->gotokey);
//		nextLead = nextLead->next;
		if(firstBlock == NULL)
			firstBlock = initialBlock;
	}

	while(nextLead != NULL)
	{
		loopflag = 0;
		condState = 0;
		//if the leader is visited or if leader has no gotokey/ending label, go to the next leader in list
		if(strcmp(initialBlock->gotokey, "\0") == 0)
		{
			prevLead = nextLead;
			nextLead = nextLead->next;	
		}
		else
		{
			//find the block with the starting label same as the ending label of the current block
			prevLead = nextLead;
			nextLead = Find(initialBlock->gotokey, initialLead);
		}

		if(isBackJump(prevLead, nextLead, initialLead) != 0)
		{
			loopflag = 1;
			loopKey = nextLead;
		}
		//add obtained leader to a basic block and connect to the list of basic blocks

		if(nextLead == NULL)
		{
			initialBlock = insertBasic(firstBlock, initialBlock, flag, prevLead);
			break;
		}
		BASIC nextBlock;
		//if the current block was not visited before
		if(nextLead->flag != 1)
		{
			nextBlock = getBasicBlock();
			nextBlock->leader = nextLead;
			if(nextLead != NULL)
			{
				strcpy(nextBlock->gotokey, nextLead->gotokey);
				strcpy(nextBlock->leadkey, nextLead->leadkey);
			}
		}
		else
		{
			//if the current block is already visited, but there needs another link to be established
			if(loopflag == 1)
				prevLead = loopKey;

			prevBlock = FindBlock(firstBlock, prevLead);
			if(loopflag!=1)
			{
				if(strcmp(prevBlock->gotokey, nextLead->leadkey) != 0)
				{
					nextBlock = FindBlock(firstBlock, nextLead);
					if(prevBlock->next[0] != nextBlock)
						prevBlock->next[0] = nextBlock;
				}
			}
		}
		if(initialBlock->leader->flag != 1)
		{
			initialBlock->leader->flag = 1;
			initialBlock = insertBasic(firstBlock, curBlock, flag , prevLead);
			flag = 0;
		}

		if(loopflag == 1)
		{
			nextBlock = FindBlock(firstBlock, nextLead);
			initialBlock->next[0] = nextBlock;
		}
		curBlock = nextBlock;

		if(loopflag == 1)
			break;
	}

	printf("\n Reached. ");
	printf("\n HERE. ");
	return initialBlock;
}

void Display(BASIC block)
{
	printf("\n Leadkey : %s , Gotokey : %s ", block->leadkey, block->gotokey);
	if(block->next[0] != NULL)
		Display(block->next[0]);
	printf("\n In current block : leadkey : %s, Gotokey : %s ", block->leadkey, block->gotokey);
	if(block->next[1] != NULL)
		Display(block->next[1]);
}


void main()
{
	FILE *fp = fopen("code.txt", "r");

	//initialising the first leader
	firstLeader = getLeader();
	LEAD prevLead, initial, curLead;
	initial = firstLeader;
	initial->line = 1;
	initial->prev = NULL;

	char nextInstr[1024], gotokey[1024], startKey[1024], prevstartKey[1024], prevgotokey[1024];
	int nextLeadFlag = 0, countInstr = 1, countLine = 0;

	//first instruction is the first leader
	fgets(initial->instr, sizeof(nextInstr), fp);
	prevLead = initial;

	while(fscanf(fp,"%s",nextInstr) != 0 )
	{
		countInstr++;
		//if the prev statement was a goto statement or if the current statement begins with a label, it is a leader
		if(nextInstr[0] != '\t' || nextLeadFlag)
		{
			//add the new leader to the list of leaders
			LEAD newLeader = getLeader();
			newLeader->line = countInstr;
			strcpy(newLeader->instr, nextInstr);

			//obtain starting label of leader
			if(nextInstr[0] != '\t')
			{
				strcpy(prevstartKey, startKey);
				getStartkey(nextInstr, startKey);
				strcpy(newLeader->leadkey, startKey);
			}
			initial = insertLead(initial, newLeader);
			if(nextLeadFlag == 1)
				strcpy(prevLead->gotokey, gotokey);
			prevLead = newLeader;
			nextLeadFlag = 0;
		}
		//if statement is goto, set nextLeadFlag and extract the ending label of the previous leader
		if(StringMatch(nextInstr, "GOTO" ,gotokey))
			nextLeadFlag = 1;
	}

	//obtain list of all basic blocks
	firstBlock = getBasicBlockList(firstBlock, initial, 0);

	curLead = initial;
	while(curLead != NULL)
	{
		if(curLead->flag != 1)
		{
			BASIC newBlock;
			newBlock = getBasicBlockList(newBlock, curLead, 0);
			firstBlock = insertBasic(firstBlock, newBlock, 1, prevLead);
		}
		prevLead = curLead;
		curLead = curLead->next;
	}


	//printing
	printf("\n\n The basic blocks are : ");
	printBasic(firstBlock);

	Display(firstBlock);
}