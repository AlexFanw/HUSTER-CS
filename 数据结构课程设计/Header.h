//
//  Header.h
//  2019SAT_word
//
//  Created by 范唯 on 2019/3/8.
//  Copyright © 2019 范唯. All rights reserved.
//

#ifndef Header_h
#define Header_h

typedef bool element;

typedef struct bool_element{
    int name;
    element sts;//该元素的状态 true or false
    struct bool_element *next;
    bool lock;//是否已经锁定
    bool back;//是否在判定列表中
}bool_element;//用于存储不同的元素

typedef struct clause_line{
    bool_element*c_element;
    bool c_element_head;//用于看在这个子句中这个bool变量的头是“是”or“非”
    bool exit;//判断这个元素在这个子句中是否存在
    struct clause_line *next; //子句中下一个元素
}clause_line;//用于储存子句中不同的元素

typedef struct clause_root{
    struct clause_root *next_root;
    clause_line *root;//用于标记子句中的第一个元素
    bool exit;//判断这个子句是否存在
}clause_root;//用于存储不同字句的根

typedef struct middle_pro{
    clause_root*firstroot;
    bool_element*middle_num;
    struct middle_pro*next;//后一个状态
    struct middle_pro*pre;//前一个状态
}middle_pro;


void clause_print(clause_root*root){
    clause_line*root_cal=root->root;
    while(root_cal!=NULL) {
        if (root_cal->c_element_head==false)
        {
            printf("-%d ",root_cal->c_element->name);
        }
        else {
            printf("%d ",root_cal->c_element->name);
        }
        root_cal=root_cal->next;
    }printf("\n");
}

clause_line*re_range_clause(clause_line*root){//将子句重排列,按照子句元素大小
    clause_line*single_range=root;//用于排列单子句的顺序
    clause_line*mark=root;
    for ( ;mark->next!=NULL;) {
        single_range=mark->next;
        for(;single_range!=NULL;)
        {
            if (mark->c_element->name > single_range->c_element->name) {
                //将两个节点的指针指向的东西交换
                clause_line exchange_root;
                exchange_root.c_element=mark->c_element;
                exchange_root.c_element_head=mark->c_element_head;
                
                
                mark->c_element=single_range->c_element;
                mark->c_element_head=single_range->c_element_head;
                
                
                single_range->c_element=exchange_root.c_element;
                single_range->c_element_head=exchange_root.c_element_head;
                
                
                single_range=single_range->next;
            }
            
            else single_range=single_range->next;
        }
        mark=mark->next;
        
    }
    return root;
}

clause_root*re_range_root(clause_root*root){
    clause_root*single_range=root;
    clause_root*mark=root;
    
    while(mark->next_root!=NULL) {
        single_range=mark->next_root;
        while(single_range!=NULL)
        {
            if (mark->root->c_element->name > single_range->root->c_element->name)
            {
                //将两个节点的指针指向的东西交换
                clause_root exchange;
                exchange.root=mark->root;
                mark->root=single_range->root;
                
                single_range->root=exchange.root;
                single_range=single_range->next_root;
            }
            else single_range=single_range->next_root;
        }
        mark=mark->next_root;
    }
    return root;
}

bool cnf_true(clause_root*cnf){
    clause_line*cnf_cal_root=cnf->root;
    while(cnf_cal_root!=NULL ) {
        if(cnf_cal_root->c_element_head==cnf_cal_root->c_element->sts)
            return true;
        else cnf_cal_root=cnf_cal_root->next;
    }
    return false ;
}//判断该子句是否成立

bool all_cnf_true(clause_root*first_root){
    clause_root*cnf_cal=first_root;
    for (; cnf_cal!=NULL;) {
        clause_root*element=cnf_cal;
        if(cnf_true(element)==false){
            clause_print(element);
            return false;
        }
        else cnf_cal=cnf_cal->next_root;
    }
    return true;
    
}//判断从该个根开始所有cnf是否成立





//    print模块：用于打印所有的cnf
void root_print_true(clause_root*root){
    clause_root*root_cal=root;
    while (root_cal!=NULL) {
        clause_line*clause_e=root_cal->root;
        if (root_cal->exit==false) {
            root_cal=root_cal->next_root;
            continue;
        }
        while( clause_e!=NULL) {
            if(clause_e->c_element_head==true&&clause_e->exit==true)printf("%d  ",clause_e->c_element->name);
            else if(clause_e->c_element_head==false&&clause_e->exit==true)printf("-%d  ",clause_e->c_element->name);
            clause_e=clause_e->next;
        }
        printf("\n");
        root_cal=root_cal->next_root;
    }}//打印全部存在的cnf

void root_print(clause_root*root){
    clause_root*root_cal=root;
    while (root_cal!=NULL) {
        clause_line*clause_e=root_cal->root;
        
        while( clause_e!=NULL) {
            if(clause_e->c_element_head==true)printf("%d  ",clause_e->c_element->name);
            else if(clause_e->c_element_head==false)printf("-%d  ",clause_e->c_element->name);
            clause_e=clause_e->next;
        }
        printf("\n");
        root_cal=root_cal->next_root;
    }}//打印所有

void clone_whole(middle_pro*head){
    middle_pro*clone_head;//创建新的head
    clone_head=(middle_pro*)malloc(sizeof(middle_pro));//分配三个指针
    clone_head->firstroot=(clause_root*)malloc(sizeof(clause_root));
    clause_root*clone_root=clone_head->firstroot;
    clone_head->next=NULL;//下一个为null
    clone_head->pre=head;
    head->next=clone_head;
    
    clause_root*root = head->firstroot;//用于追踪
    int flag=0;//用于判断这个表中还存不存在子句
    clause_root*pre_root=NULL;
    while (root!=NULL)
    {
        if (root->exit==true)
        {
            flag=1;
            int clause_flag=0;//用于判断这个子句中存不存在东西。
            clause_line*line_follow=root->root;//追踪整个子句。
            
            clone_root->root=(clause_line*)malloc(sizeof(clause_line));
            clone_root->exit=true;
            clause_line*line_clone=clone_root->root;//创建第一个根的第一个元素
            
            clause_line*pre_one=NULL;
            while(line_follow!=NULL){
                if (line_follow->exit==true) {
                    clause_flag=1;
                    line_clone->c_element=line_follow->c_element;
                   // printf("%d ",line_follow->c_element->name);
                    line_clone->c_element_head=line_follow->c_element_head;
                    line_clone->exit=true;
                    line_clone->next=(clause_line*)malloc(sizeof(clause_line));
                    
                    if (line_follow->next==NULL) {
                        free(line_clone->next);
                        line_clone->next=NULL;
                        break;
                    }
                    pre_one=line_clone;
                    line_clone=line_clone->next;
                    line_follow=line_follow->next;
                }
                
                else if (line_follow->exit==false){
                    line_follow->exit=true;//这个元素不存在了
                    
                    if (line_follow->next==NULL) {
                        free(line_clone);//如果元素不存在了。那么
                        line_clone=NULL;
                        
                        pre_one->next=NULL;
                        break;
                    }
                    line_follow=line_follow->next;//跳到下一个元素
                    
                }
                
            }//克隆整个子句
            
            
            if (clause_flag==0) {
                if (root->next_root!=NULL) {
                    root=root->next_root;//进入下一个根
                }
                else {
                    free(clone_root);
                    pre_root->next_root=NULL;//下一个根没有了，那么就结束
                    break;
                }
            }//子句中不存在东西了
            
            else if (clause_flag==1){
                clone_root->next_root=(clause_root*)malloc(sizeof(clause_root));
                if (root->next_root==NULL) {
                    free(clone_root->next_root);
                    clone_root->next_root=NULL;
                    break;
                }
                pre_root=clone_root;
                clone_root=clone_root->next_root;
                root=root->next_root;//进入下一个根
                //printf("\n");
            }
        }
        
        else if(root->exit==false)
        {
            root->exit=true;
            if (root->next_root!=NULL) {
                root=root->next_root;//进入下一个根
            }
            else {
                free(clone_root);
                
                if(pre_root!=NULL)pre_root->next_root=NULL;//下一个根没有了，那么就结束
                break;
            }
        }
    }//克隆所有根
    
    if (flag==0) {
        clone_head->firstroot=NULL;
    }//如果没有东西了那么就free掉开始分配的空间
    
}





typedef struct double_back{
    struct double_back*pre;//前一个元素
    bool_element*bol;//当前元素
    struct double_back*next;//后一个元素
    
}double_back;



int check_s(clause_root*root){
    int ele_num=0;
    int single_num=0;
    clause_line*line=root->root;
    if (root->exit==false) {
        return 0;
    }//如果该子句不存在了，那么就返回0
    while (line!=NULL) {
        if (line->exit==true) {
            ele_num+=1;
            single_num=line->c_element->name;
            line=line->next;
        }
        else if(line->exit==false){
            line=line->next;
        }
    }
    if (ele_num==1) {
        return single_num;
    }
    else return 0;
    
}//检查一个子句中是不是只有一个元素了,返回元素名称

int single_clause(clause_root*head){
    int sin_num=0;
    clause_line*single_head=head->root;
    if ((sin_num=check_s(head))!=0) {//当这个子句中只有这个元素时,需要修改
        while(single_head!=NULL){
            if (single_head->c_element->name==sin_num) {
                single_head->exit=false;//这个子句直接消失
                single_head->c_element->sts=single_head->c_element_head;
                return sin_num;
            }
            else single_head=single_head->next;
        }
        return 0;
    }
    else return 0;
}

//------------------数独生成
void rank(int *x, int *y)
{
    int t;
    t = *x;
    *x = *y;
    *y = t;
}

bool check(int a[9][9], int n)
{
    int i, j;
    for (i = 0; i < 9; i++)
        for (j = 0; j < i; j++)
            if (a[i][n * 3] == a[j][n * 3])
                return false;
    return true;
}

void create_sudo(int sudo_final[9][9])
{
    int a[9][9] = { 0 };
    int *p[3][3], *m[3][6], *n[3][6], *r[9][4], *aa[9][9];
    int **q[9];
    int i, j, k, l, h, t= 0;
    void rank(int *x, int *y);
    bool check(int a[9][9], int n);
    
    srand( (unsigned)time( NULL ) );
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            p[i][j] = &a[i * 3 + 1][j * 3 + 1];
    for (k = 0; k < 9; k++)
        q[k] = &p[k / 3][k % 3];
    for (i = 0; i < 3; i++)
        for (j = 0; j < 6; j++)
        {
            m[i][j] = &a[i * 3 + 1][2 * j - j / 2];
            n[i][j] = &a[2 * j - j / 2][i * 3 + 1];
        }
    for (k = 0; k < 9; k++)
        for (l = 0; l < 4; l++)
            r[k][l] = &a[(k / 3) * 3 + (l / 2) * 2][(k % 3) * 3 + (l % 2) * 2];
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
            aa[i][j] = &a[i][j];
step1:
    for (i = 0; i < 9; i++)
    {
    next1:
        **q[i] = rand() % 10;
        if (**q[i] == 0)
            goto next1;
        for (j = 0; j < i; j++)
            if (**q[j] == **q[i])
                goto next1;
    }
step2:
    for (i = 0; i < 3; i++)
        for (j = 0; j < 6; j++)
        {
        next2:
            *m[i][j] = rand() % 10;
            if (*m[i][j] == 0)
                goto next2;
            for (k = 0; k < 3; k++)
                if (*m[i][j] == *p[i][k])
                    goto next2;
            for (k = 0; k < j; k++)
                if (*m[i][j] == *m[i][k])
                    goto next2;
            for (k = 0; k < i; k++)
                if (*m[i][j] == *m[k][j])
                    goto step2;
        }
step3:
    for (i = 0; i < 3; i++)
    {
    next4:
        for (j = 0; j < 6; j++)
        {
        next3:
            *n[i][j] = rand() % 10;
            if (*n[i][j] == 0)
                goto next3;
            for (k = 0; k < 3; k++)
                if (*n[i][j] == *p[k][i])
                    goto next3;
            for (k = 0; k < j; k++)
                if (*n[i][j] == *n[i][k])
                    goto next3;
            for (l = 0; l < 2; l++)
            {
                if (*n[i][j] == *m[j / 2][i * 2 + l])
                    goto next4;
            }
            for (k = 0; k < i; k++)
                if (*n[i][j] == *n[k][j])
                    goto step3;
        }
    }
step4:
    for (i = 0; i < 3; i++)
    {
        for (h = 0; h < 2; h++)
        {
        next6:
            for (l = 0; l < 3; l++)
                for (j = 0; j < 2; j++)
                {
                next5:
                    *r[i * 3 + l][h * 2 + j] = rand() % 10;
                    if (*r[i * 3 + l][h * 2 + j] == 0)
                        goto next5;
                    if (*r[i * 3 + l][h * 2 + j] == **q[i * 3 + l])
                        goto next5;
                    for (k = 0; k < h * 2 + j; k++)
                        if (*r[i * 3 + l][h * 2 + j] == *r[i * 3 + l][k])
                            goto next5;
                    for (k = 0; k < 2; k++)
                    {
                        if (*r[i * 3 + l][h * 2 + j] == *m[i][l * 2 + k])
                            goto next5;
                        if (*r[i * 3 + l][h * 2 + j] == *n[l][i * 2 + k])
                            goto next5;
                    }
                    for (k = 0; k <= l * 3 + j * 2; k++)
                        for (t = 0; t < k; t++)
                            if (a[i * 3 + h * 2][k] == a[i * 3 + h * 2][t])
                                goto next6;
                }
        }
    }
step5:
    for (i = 0; i < 3; i++)
    {
        if (check(a, i) == false)
        {
            for (j = 0; j < 9; j++)
            {
                rank(aa[j][i * 3], aa[j][i * 3 + 2]);
                if (check(a, i) == false)
                    rank(aa[j][i * 3], aa[j][i * 3 + 2]);
                else if (check(a, i) == true)
                    break;
            }
        }
        if (check(a, i) == false)
        {
            for (j = 0; j < 9; j++)
            {
                for (k = 8; k > j; k--)
                {
                    rank(aa[j][i * 3], aa[j][i * 3 + 2]);
                    rank(aa[k][i * 3], aa[k][i * 3 + 2]);
                    if (check(a, i) == false)
                    {
                        rank(aa[j][i * 3], aa[j][i * 3 + 2]);
                        rank(aa[k][i * 3], aa[k][i * 3 + 2]);
                    }
                    else if (check(a, i) == true)
                        break;
                }
                if (check(a, i) == true)
                    break;
            }
        }
        if (check(a, i) == false)
        {
            for (l = 0; l < 9; l++)
            {
                for (j = l + 1; j < 9; j++)
                {
                    for (k = 8; k > j; k--)
                    {
                        rank(aa[l][i * 3], aa[l][i * 3 + 2]);
                        rank(aa[j][i * 3], aa[j][i * 3 + 2]);
                        rank(aa[k][i * 3], aa[k][i * 3 + 2]);
                        if (check(a, i) == false)
                        {
                            rank(aa[l][i * 3], aa[l][i * 3 + 2]);
                            rank(aa[j][i * 3], aa[j][i * 3 + 2]);
                            rank(aa[k][i * 3], aa[k][i * 3 + 2]);
                        }
                        else if (check(a, i) == true)
                            break;
                    }
                    if (check(a, i) == true)
                        break;
                }
                if (check(a, i) == true)
                    break;
            }
        }
        if (check(a, i) == false)
        {
            for (l = 0; l < 6; l++)
            {
                for (h = l + 1; h < 7; h++)
                {
                    for (j = h + 1; j < 8; j++)
                    {
                        for (k = 8; k > j; k--)
                        {
                            rank(aa[l][i * 3], aa[l][i * 3 + 2]);
                            rank(aa[h][i * 3], aa[h][i * 3 + 2]);
                            rank(aa[j][i * 3], aa[j][i * 3 + 2]);
                            rank(aa[k][i * 3], aa[k][i * 3 + 2]);
                            if (check(a, i) == false)
                            {
                                rank(aa[l][i * 3], aa[l][i * 3 + 2]);
                                rank(aa[h][i * 3], aa[h][i * 3 + 2]);
                                rank(aa[j][i * 3], aa[j][i * 3 + 2]);
                                rank(aa[k][i * 3], aa[k][i * 3 + 2]);
                            }
                            else if (check(a, i) == true)
                                break;
                        }
                        if (check(a, i) == true)
                            break;
                    }
                    if (check(a, i) == true)
                        break;
                }
                if (check(a, i) == true)
                    break;
            }
        }
        if (check(a, i) == false)
            goto step4;
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sudo_final[i][j]=a[i][j];
        }
    }
    
    
    
}//数独生成
//----------------end

int dpll_cnf(clause_root*first_root,int bol_number,bool_element*b_element_point[])
{
    middle_pro*first_pro;
    first_pro=(middle_pro*)malloc(sizeof(first_pro));
    first_pro->firstroot=first_root;
    first_pro->pre=NULL;
    middle_pro*first_pro_cal=first_pro;//用于循环
    first_pro->pre=NULL;
    //模块5:DPLL算法
    double_back*list_back=NULL;
    int list_back_num=0;//检查list_back中的总人数
    while (list_back_num!=bol_number) {
        //list还没满时就开始循环
        //root_print_true(first_pro_cal->firstroot);
        clause_root*check_single=first_pro_cal->firstroot;//用于查找单子句！！！！！
        int flag_single=0;
        
        while (check_single!=NULL) {
            if((flag_single=single_clause(check_single))!=0){//存在单子句
                if (list_back==NULL) {
                    list_back=(double_back*)malloc(sizeof(double_back));
                    list_back->pre=NULL;
                    list_back->next=NULL;
                }//创建新的单子句元素
                else{
                    double_back*clo=list_back;
                    list_back->next=(double_back*)malloc(sizeof(double_back));
                    list_back=list_back->next;
                    list_back->pre=clo;
                    list_back->next=NULL;
                }
                list_back->bol=b_element_point[flag_single-1];
                b_element_point[flag_single-1]->back=true;//入队列
                b_element_point[flag_single-1]->lock=true;//上锁
                
                list_back_num+=1;
                //                printf("\n存在单子句——%d\n",list_back->bol->name);
                break;
            }
            else check_single=check_single->next_root;//不存在就跳过
        }//遍历整个列表看看有没有单子句,有单子句就跳出，这个时候single号元素就是确定的
        
        int flag_single_false=0;//如果不存在单子句。那么加入一个判定元素
        if (flag_single!=0) {
            //            printf("\n");
        }//存在单子句
        else {
            for (int i=0; b_element_point[i]->back==true; i++){
                flag_single_false=b_element_point[i]->name;
            }
            flag_single_false+=1;//新的判定元素的名字！！！！！！！！！！！！！！！！！！！
            
            double_back*clone_list=list_back;
            if (list_back==NULL) {
                list_back=(double_back*)malloc(sizeof(double_back));
                list_back->pre=NULL;
                list_back->next=NULL;
            }
            else{
                double_back*clo=list_back;
                list_back->next=(double_back*)malloc(sizeof(double_back));
                list_back=list_back->next;
                list_back->pre=clo;
                list_back->next=NULL;
            }
            
            list_back->bol=b_element_point[flag_single_false-1];
            
            b_element_point[flag_single_false-1]->back=true;//入队
            b_element_point[flag_single_false-1]->lock=false;//没锁定
            
            list_back_num+=1;
            list_back->next=NULL;
            list_back->pre=clone_list;//创造下一个判定元素
            clone_whole(first_pro_cal);//并且入栈一个新的中间状态
            //            printf("\n");
            first_pro_cal=first_pro_cal->next;//指针指向下一个
            
            first_pro_cal->middle_num=b_element_point[flag_single_false-1];//!!!!!!!!!!
            //root_print(first_pro_cal->firstroot);
        }//不存在单子句时加入判定元素并且入一个新的状态
        
        
        int delete_num=0;//用于看要删除哪一个元素
        if (flag_single!=0) {
            delete_num=flag_single;
        }
        else if(flag_single_false!=0){
            delete_num=flag_single_false;
        }//看要删除的是单子句元素还是判定元素
        //找到判定元素delete_num和delete_element
        
        
        
        
    reback:if(delete_num!=0){//当还有元素可以删除时
        
        clause_root*delete_element=first_pro_cal->firstroot;//用于循环删除。当前的状态
        
        //        printf("\n我们现在准备删除%d元素\n",delete_num);
        int flag_check=0;//检查冲突！！！！！！！！！！
        
        while(delete_element!=NULL)//检查每个子句
        {
            if (delete_element->exit==false) {//子句不存在
                delete_element=delete_element->next_root;
            }
            else{
                int theone=check_s(delete_element);//检查这个子句是否有单个元素存在，theone如果不等于delte_num就跳过
                clause_line*check_sin=delete_element->root;
                while (check_sin!=NULL) {//检查每个元素
                    if(theone!=0   &&    check_sin->c_element->name==delete_num   &&   b_element_point[delete_num-1]->sts!=check_sin->c_element_head)//有单元素，单的数字正好但是状态不一样，矛盾
                    {
                        flag_check=1;
                        break;
                    }
                    else if (check_sin->c_element->name==delete_num   &&   b_element_point[delete_num-1]->sts==check_sin->c_element_head)//状态一样，删除这个子句
                    {
                        //check_sin->exit=false;就不删除这个元素了
                        delete_element->exit=false;//这个子句直接被删除
                        break;
                    }
                    else if (theone == 0 &&check_sin->c_element->name==delete_num&&check_sin->c_element_head!=check_sin->c_element->sts)//无单元素，但是这个元素在这个子句中不对
                    {
                        check_sin->exit=false;
                        check_sin=check_sin->next;
                        //printf("1");
                    }
                    else {//不是这个东西
                        //printf("0");
                        check_sin=check_sin->next;
                    }
                }//检查这个子句中的每个元素  while
                if (flag_check==1) {
                    break;
                }//有冲突
                else delete_element=delete_element->next_root;//没有冲突
            }
        }
        
        //        root_print_true(first_pro_cal->firstroot);
        
        if(flag_check==1)
        {
            if(b_element_point[delete_num-1]->lock==false)
            {
                b_element_point[delete_num-1]->lock=true;
                if(b_element_point[delete_num-1]->sts==true)b_element_point[delete_num-1]->sts=false;
                else b_element_point[delete_num-1]->sts=true;//更改状态
                
                //                printf("更改%d并且回到开头\n",b_element_point[delete_num-1]->name);
                //root_print(first_pro_cal->firstroot);
                first_pro_cal=first_pro_cal->pre;//回到前一个列表
                
                free(first_pro_cal->next);
                first_pro_cal->next=NULL;
                clone_whole(first_pro_cal);
                first_pro_cal=first_pro_cal->next;//删了重来
                
                int middle=b_element_point[delete_num-1]->name;//重来一遍
                delete_num=middle;
                goto reback;
            }
            
            else if (b_element_point[delete_num-1]->lock==true){
                while (list_back->bol->lock==true)
                {
                    list_back->bol->back=false;//出队列
                    list_back->bol->lock=false;//出队列
                    list_back->bol->sts=true;//更改为默认状态
                    list_back_num-=1;
                    list_back=list_back->pre;
                    if (list_back==NULL) {
                        return 0;
                    }//已经没有元素可以删除了
                    free(list_back->next);
                    list_back->next=NULL;
                }
                delete_num = list_back->bol->name;//删除的元素更改
                
                while(first_pro_cal->middle_num->name!=b_element_point[delete_num-1]->name){
                    first_pro_cal=first_pro_cal->pre;
                    free(first_pro_cal->next);
                    first_pro_cal->next=NULL;
                }//找到那个元素
                
                clause_root*recall=first_pro_cal->firstroot;
                
                while (recall!=NULL) {
                    clause_line*recall_line=recall->root;
                    recall->exit=true;
                    while (recall_line!=NULL)
                    {
                        recall_line->exit=true;
                        recall_line->c_element->back=false;
                        recall_line->c_element->lock=false;
                        recall_line=recall_line->next;
                        
                        
                    }
                    recall=recall->next_root;
                }//还原所有子句
                b_element_point[delete_num-1]->lock=true;
                b_element_point[delete_num-1]->back=true;
                
                if(b_element_point[delete_num-1]->sts==true)b_element_point[delete_num-1]->sts=false;
                else b_element_point[delete_num-1]->sts=true;//切换状态
                int middle=b_element_point[delete_num-1]->name;
                delete_num=middle;
                goto reback;
            }
        }//回溯
    }
    else return 0;//
    }
    return 1;
}

#endif /* Header_h */
