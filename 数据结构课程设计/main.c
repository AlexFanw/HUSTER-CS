//
//  main.c
//  2019SAT_word
//
//  Created by 范唯 on 2019/3/8.
//  Copyright © 2019 范唯. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Header.h"
int main() {
    
    printf("Checking File...\n");
    char*filename;
    FILE*fp;
    filename="/Users/alexfan/Desktop/University/2019数据结构课程设计/综合程序设计任务及指导学生包/SAT测试备选算例/基准算例/功能测试/sat-20.cnf";
    filename="/Users/alexfan/Desktop/University/2019数据结构课程设计/综合程序设计任务及指导学生包/SAT测试备选算例/满足算例/M/sud00001.cnf";
//    filename="/Users/alexfan/Desktop/University/2019数据结构课程设计/综合程序设计任务及指导学生包/SAT测试备选算例/基准算例/性能测试/ais10.cnf";//算不出来
//        filename="/Users/alexfan/Desktop/University/2019数据结构课程设计/综合程序设计任务及指导学生包/SAT测试备选算例/满足算例/S/problem3-100.cnf";//很慢
    
    //   filename="/Users/alexfan/Desktop/University/2019数据结构课程设计/综合程序设计任务及指导学生包/SAT测试备选算例/满足算例/M/problem5-200.cnf";//算不出来
    //    filename="/Users/alexfan/Desktop/University/2019数据结构课程设计/综合程序设计任务及指导学生包/SAT测试备选算例/满足算例/M/problem12-200.cnf";//算不出来
    //    filename="/Users/alexfan/Desktop/University/2019数据结构课程设计/综合程序设计任务及指导学生包/SAT测试备选算例/满足算例/M/bart17.shuffled-231.cnf";//算不出来
    //    filename="/Users/alexfan/Desktop/University/2019数据结构课程设计/综合程序设计任务及指导学生包/SAT测试备选算例/满足算例/M/m-mod2c-rand3bip-sat-220-3.shuffled-as.sat05-2490-311.cnf";//算不出来
    //filename="";
    //    filename="/Users/alexfan/Desktop/University/2019数据结构课程设计/综合程序设计任务及指导学生包/SAT测试备选算例/满足算例/L/eh-dp04s04.shuffled-1075.cnf";
    fp=fopen(filename,"r");
    int ch;
    char p[50],cnf[50];
    char pp='p';
    int bol_number=0;
    int clause_number=0;
    fscanf(fp,"%s",p);
    while (1) {
        if(strcmp(p,&pp)==0){
            printf("File in order\n");
            break;
        }
        else fscanf(fp,"%s",p);
    }//跳过第一行
    fscanf(fp, "%s %d %d",cnf,&bol_number,&clause_number);
    printf("%s %s %d %d\n",p,cnf,bol_number,clause_number);//读取打印第一行有效信息
    fscanf(fp,"%d",&ch);
    
    clock_t start,finish;
    double duration;
    start=clock();
    
    //模块1:创建所有bool元素
    bool_element one;
    bool_element *b_element=&one;
    bool_element *b_element_cal=b_element;
    for (int i=1; i<=bol_number; ++i) {
        b_element_cal->sts=true;
        b_element_cal->name=i;
        b_element_cal->lock=false;//不上锁
        b_element_cal->back=false;//不在判定列表
        if((b_element_cal->next=(bool_element*)malloc(sizeof(bool_element)))==NULL)exit(-5);
        
        if(i<bol_number)b_element_cal=b_element_cal->next;
        else{
            free(b_element_cal->next);
            b_element_cal->next=NULL;
            break;
        }
    }
    bool_element*b_element_point[bol_number];
    bool_element*b=b_element;
    for (int i=0; b!=NULL; i++) {
        b_element_point[i]=b;
        b=b->next;
    }
    //模块1:end——创建所有的bol值
    
    
    //模块2：创建所有子句
    clause_root *first_root;
    first_root=(clause_root*)malloc(sizeof(clause_root));
    first_root->exit=true;
    first_root->root=(clause_line*)malloc(sizeof(clause_line));
    if(ch!=0){
        int ch_abs_first=abs(ch);
        first_root->root->c_element=b_element_point[ch_abs_first-1];
        first_root->root->exit=true;
        if(ch<0) first_root->root->c_element_head=false;
        else first_root->root->c_element_head=true;
        
        //        printf("第一个子句的根为%d",first_root->root->c_element->name);
    }//创建第一个子句的根
    else exit(-1);
    clause_root*root_cal=first_root;
    while (1) {
        if(ch==0){
            if(fscanf(fp, "%d", &ch)>0){
                if(ch==0) exit(-1);//空子句，错误
                else if (ch!=0){//如果新读入的ch不为0，那么就创建一个新的根
                    if((root_cal->next_root=(clause_root*)malloc(sizeof(clause_root)))==NULL)exit(-6);
                    root_cal=root_cal->next_root;
                    root_cal->exit=true;
                    int ch_abs_0=abs(ch);
                    //                    printf("根:%d\n",ch);
                    if ((root_cal->root=(clause_line*)malloc(sizeof(clause_line)))==NULL)exit(-7);
                    
                    root_cal->root->c_element=b_element_point[ch_abs_0-1];
                    root_cal->root->exit=true;
                    if(ch<0) root_cal->root->c_element_head=false;
                    else root_cal->root->c_element_head=true;
                }
                else break;
            }
            else break;
        }
        else if(ch!=0){
            clause_line*clause_element=root_cal->root;
            while(ch!=0){//当前ch是根，需要再读一次
                if(fscanf(fp, "%d", &ch)>0){
                    if(ch==0) {
                        clause_element->next=NULL;//创建一个循环链表
                        break;
                    }
                    else{
                        if((clause_element->next=(clause_line*)malloc(sizeof(clause_line)))==NULL)exit(-8);
                        clause_element=clause_element->next;
                        int ch_abs_1=abs(ch);
                        
                        clause_element->c_element=b_element_point[ch_abs_1-1];
                        clause_element->exit=true;//该元素在子句中是存在的
                        if(ch<0)clause_element->c_element_head=false;
                        else clause_element->c_element_head=true;
                    }}}}}
    //模块2:end——创建所有子句
    //模块1和2结束后，我们现在获得了fisrt_root 和b_elementl两个指针，一个里面存了所有的子句，一个存了y所有的元素
    
    //模块3:将所有子句内部按照大小重排列
    clause_root*exchange_clause=first_root;
    while(exchange_clause!=NULL) {
        clause_line*range_clause=exchange_clause->root;
        range_clause=re_range_clause(range_clause);
        for (; range_clause!=NULL; ) {
            range_clause=range_clause->next;
        }
        exchange_clause=exchange_clause->next_root;
    }
    //模块3——end
    
    //模块4:将所有子句的根按照大小重新排列
//    clause_root*exchange_root=first_root;
//    first_root=re_range_root(exchange_root);
//    root_print(first_root);
    //模块4-end
    
    //模块5:DPLL算法
    dpll_cnf(first_root, bol_number, b_element_point);
    //    模块5——end
    if(all_cnf_true(first_root)==false)printf("s:0\n");
    else printf("s:1\n");
    
    bool_element*bool_element_cal=b_element;
    printf("v:");
    while (bool_element_cal!=NULL) {
        if (bool_element_cal->sts==true) {
            printf("%d ",bool_element_cal->name);
        }
        else printf("-%d ",bool_element_cal->name);
        bool_element_cal=bool_element_cal->next;
    }//打印所有元素的状态。最终结果
    
    
    
    
    
    
    fclose(fp);
    fp=NULL;
    free(first_root->next_root);
    first_root->next_root=NULL;
    free(b_element->next);
    free(first_root);
    first_root=NULL;
    b_element->next=NULL;
    finish=clock();
    duration=(double)(finish - start)/CLOCKS_PER_SEC;
    printf("\nt:%fms\n",1000*duration);
    
    return 0;
    
}


