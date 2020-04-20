#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cachelab.h"
//所有struct和function
typedef struct line{
  int age;          // 使用次数
  char valid;     //有效位
  int tag;      //组号
  int* block; //块
  } line;

typedef struct group{
    line* lines; // 每一组有多少行
} group;

typedef struct cache{
  group* groups;    // 每一个cache有多少组
} cache;
/****************************************************************************************************************************/
cache* createCache(int groupNum, int lineNum);
line createLine(int tag, int blockSize, int memAddr);
void releaseCache(cache* c, int groups, int lines);
void incrementAge(group* cur_group, int lines);
int calculateAddr(char* fileLine, long* memAddr);
void recordHME(group* cur_group, int lines, int tag, int blockSize, long memAddr,int* hits, int* misses, int* evictions);
void recordHME_verbose(int* oldHits, int* oldMisses, int* oldEvictions,int* hits, int* misses, int* evictions);
void excute(int s, int E, int b, FILE* file, int v,int* hits, int* misses, int* evictions);
void help();
/****************************************************************************************************************************/
int main(int argc, char **argv){

    int v = 0;
    int s, E, b, i;
    FILE* file; 
    
    for(i = 1; i < argc; ++i){
        char* arg = *(argv + i);
        char* nextarg = *(argv + i + 1);
        if(strcmp(arg, "-v") == 0){
            v = 1;
        } else if(strcmp(arg, "-s") == 0){
            s = atoi(nextarg);
            i++;
        } else if(strcmp(arg, "-E") == 0){
            E = atoi(nextarg);
            i++;
        } else if(strcmp(arg, "-b") == 0){
            b = atoi(nextarg);
            i++;
        } else if(strcmp(arg, "-t") == 0){
            file = fopen(nextarg, "r");
            i++;
        } else if(strcmp(arg, "-h") ==0){
            help();
        }
    }
    int hits, misses, evictions;
    excute(s, E, b, file, v, &hits, &misses, &evictions);  
    printSummary(hits, misses, evictions);
    return 0;}
/*
创建新的cache
创建groupNum个组
每个组内创建lineNum行
并且把每行的valid置为0
*/
cache *createCache(int groupNum, int lineNum){
  cache* newCache = (cache*) malloc(sizeof(cache));
  group* new_groups = (group*) malloc(groupNum * sizeof(group));
  newCache->groups = new_groups;
  for(int i = 0; i < groupNum; i++){
      line* new_lines = (line*) malloc(lineNum * sizeof(line));
      for(int j = 0; j < lineNum; j++){
          new_lines[j].valid = 0;
      }
      new_groups[i].lines = new_lines;
  }
  return newCache;}
//创建新的行。
line createLine(int tag, int blockSize, int memAddr){
    line newline;
    newline.valid = 1;
    newline.age = -1;
    newline.tag = tag;
    int* newBlock = (int*) malloc(blockSize * sizeof(int));//根据块大小来定
    int byteNum = memAddr & (blockSize - 1);
    for(int i = 0; i < blockSize; i++){
        newBlock[i] = memAddr - byteNum + i;
    }
    newline.block = newBlock;
    return newline;}
/*
递归释放Cache
*/
void releaseCache(cache* c, int groups, int lines){
    for(int i = 0; i < groups; i++){
        for(int j = 0; j < lines; j++){
            free(c->groups[i].lines[j].block);
        }
        free(c->groups[i].lines);
    }
    free(c->groups);
    free(c);
    return;}
/* 将所有此轮次没有命中的行的age ++1 */
void incrementAge(group* cur_group, int lines){
    for(int i = 0; i < lines; i++){
        if(cur_group->lines[i].valid == 1){
            cur_group->lines[i].age += 1;
        }
    }
    return;}
/*计算出要访问的主存地址以及字节长度*/
int calculateAddr(char* fileLine, long* memAddr){
    int addrlen = 0;
    while(fileLine[3 + addrlen] != ','){
        addrlen++;
    }
    char* addr = (char*) malloc(addrlen * sizeof(char));
    int i = 0;
    do{
        addr[i] = fileLine[i + 3];//0400d7d4地址位
        i++;
    } while(i < addrlen);
    *(addr + addrlen) = '\0';//拼接字符串
    *memAddr = strtol(addr, NULL, 16);
    free(addr);
    return addrlen;}//字节长度

/* 计算出Hit/Miss/Eviction的次数 */
void recordHME(group* cur_group, int lines, int tag, int blockSize, long memAddr,int* hits, int* misses, int* evictions){
    int InvalidLine = -1;
    int evictionLine = -1;
    int max_age = 0;
    for(int i = 0; i < lines; i++){//实现多路选择器
        if((cur_group->lines[i].valid == 1) && (cur_group->lines[i].tag == tag)){
            *hits += 1;
            cur_group->lines[i].age = -1;
            incrementAge(cur_group, lines);//增加该组中其他没命中的line的age
            return;
        } else if((InvalidLine == -1) && (cur_group->lines[i].valid == 0)){
            InvalidLine = i;//记录没被用的line
        } else if((cur_group->lines[i].valid == 1) && (cur_group->lines[i].age >= max_age)){
            evictionLine = i;//当前需要被替换的行
            max_age = cur_group->lines[i].age;
        }
    }
    *misses += 1;
    if(InvalidLine != -1){//先选择填满Invalid的行
        cur_group->lines[InvalidLine] = createLine(tag, blockSize, memAddr);
        incrementAge(cur_group, lines);
    } else{//把年纪最大的替换
        *evictions += 1;
        free(cur_group->lines[evictionLine].block);
        cur_group->lines[evictionLine] = createLine(tag, blockSize, memAddr);
        incrementAge(cur_group, lines);
    }
    return;
}
//详细记录Hit/Miss/Eviction
void recordHME_verbose(int* oldHits, int* oldMisses, int* oldEvictions,int* hits, int* misses, int* evictions){
    if(*misses > *oldMisses){
        *oldMisses = *misses;
        printf(" miss");
    }
    if(*evictions > *oldEvictions){
        *oldEvictions = *evictions;
        printf(" eviction");
    }
    if(*hits > *oldHits){
        *oldHits = *hits;
        printf(" hit");
    }
    return;}
                       
/*运行模拟Cache*/
void excute(int s, int E, int b, FILE* file, int v,int* hits, int* misses, int* evictions){
    *hits = 0;
    *misses = 0;
    *evictions = 0;

    int groups = pow(2,s),
        blockSize = pow(2,b);
    cache* simCache = createCache(groups, E);

    char* fileLine = NULL;//文件行指针
    size_t len = 0; //每一个line的长度
    ssize_t read;

    if(v == 1){
        int oldHits = *hits;
        int oldMisses = *misses;
        int oldEvictions = *evictions;
        while((read = getline(&fileLine, &len, file)) != -1){//逐行解析
            char* printLine = fileLine;
            printLine[strlen(printLine) - 1] = '\0';
            printf("%s", printLine);
            if(fileLine[0] == 'I'){continue;}
            
            long memAddr;
            int addrlen = calculateAddr(fileLine, &memAddr);
            int groupNum = (memAddr >> b) & (groups - 1);
            group* cur_group = &(simCache->groups[groupNum]); 
            int maxTag = pow(2,(4 * addrlen) - s - b) - 1;
            int tag = (memAddr >> (s + b)) & maxTag;
            char acctype = fileLine[1];             
            if(acctype == 'M'){ //两次访存
                recordHME(cur_group, E, tag, blockSize, memAddr, hits, misses, evictions);
                recordHME_verbose(&oldHits, &oldMisses, &oldEvictions, hits, misses, evictions);
                recordHME(cur_group, E, tag, blockSize, memAddr, hits, misses, evictions);
                recordHME_verbose(&oldHits, &oldMisses, &oldEvictions, hits, misses, evictions);
            } else if(acctype == 'S' || acctype == 'L'){//一次访存
                recordHME(cur_group, E, tag, blockSize, memAddr, hits, misses, evictions);
                recordHME_verbose(&oldHits, &oldMisses, &oldEvictions,hits, misses, evictions);
            } else {printf ("Error");}
            printf("\n");
        }
    } else{
        while((read = getline(&fileLine, &len, file)) != -1){
            if(fileLine[0] == 'I'){continue;}
            long memAddr;
            int addrlen = calculateAddr(fileLine, &memAddr);
            int groupNum = (memAddr >> b) & (groups - 1);
            group* cur_group = &(simCache->groups[groupNum]); 
            int maxTag = pow(2,(4 * addrlen) - s - b) - 1;
            int tag = (memAddr >> (s + b)) & maxTag;
            char acctype = fileLine[1];       

            if(acctype == 'M'){ // 两次访存
                recordHME(cur_group, E, tag, blockSize, memAddr, hits, misses, evictions);
                recordHME(cur_group, E, tag, blockSize, memAddr, hits, misses, evictions);
            } else if(acctype == 'S' || acctype == 'L'){//一次访存
                recordHME(cur_group, E, tag, blockSize, memAddr, hits, misses, evictions);
            } else {printf ("Error");}
        }
    }
    fclose(file);
    free(fileLine);
    releaseCache(simCache, groups, E);
    return;} 
//帮助文档
void help(){
    printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n"
            "Options:\n"
            "\t-h\tPrint this help message.\n"
            "\t-v\tOptional v flag.\n"
            "\t-s <num>\tNumber of group index bits.\n"
            "\t-E <num>\tNumber of lines per group.\n"
            "\t-b <num>\tNumber of block offgroup bits.\n"
            "\t-t <file>\tTrace file.\n\n"
            "Examples:\n"
            "\tlinux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.file\n"
            "\tlinux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.file\n");}