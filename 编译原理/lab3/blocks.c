#include "def.h"

codenode *splitBlock(codenode *head)
{
    codenode *p = head;
    int num;
    //找出所有GOTO涉及的Label
    int *labelsTable = findAllGOTOLabel(head);
    //在开始语句之前生成一句block
    p = merge(2, genBlock(newBlock()), p);
    head = p;
    do
    {
        //当前节点是LABEL，并且前驱节点不是BLOCK
        if (p->op == LABEL)
        {
            sscanf(&(p->result.id[5]), "%d", &num);
            if (labelsTable[num] == 1 && p->prior->op != BLOCK)
            {
                p = merge(2, genBlock(newBlock()), p);
            }
        }
        //当前节点是跳转，且下条语句不是BLOCK
        if ((p->op == GOTO || p->op == JGE || p->op == JGT || p->op == JLE || p->op == JLT ||
             p->op == EQ || p->op == NEQ || p->op == RETURN) &&
            p->next->op != BLOCK)
            p->next = merge(2, genBlock(newBlock()), p->next);
        p = p->next;
    } while (head != p);
    return head;
}

int *findAllGOTOLabel(codenode *head)
{
    codenode *p = head;
    int totals; //得知有多少个label
    char *tmp = newLabel();
    sscanf(&(tmp[5]), "%d", &totals);
    int *labelsTable = (int *)malloc(sizeof(int) * (totals + 1));
    do
    {
        if (p->op == GOTO)
        {
            sscanf(&(p->result.id[5]), "%d", &totals);
            labelsTable[totals] = 1;
        }
        p = p->next;
    } while (p != head);
    return labelsTable;
}

codenode *genBlock(char *label)
{
    codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = BLOCK;
    strcpy(h->result.id, label);
    h->next = h->prior = h;
    return h;
}

char *newBlock()
{
    static int no = 1;
    char s[10];
    //itoa(no++, s, 10);
    snprintf(s, 10, "%d", no++);
    return strcat0("block", s);
}
