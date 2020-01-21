#ifndef MAIN_H_
#define MAIN_H_

#include<dirent.h>
#include<time.h>
int printdir(char *dir, int depth);//总递归打印函数
int printdetail(struct dirent *entry, int fmtLinkWidth, int fmtSizeWidth);//目录信息打印
int sortdir(const void *a, const void *b);//目录排序
#define LS_BLOCK_SIZE 1024
#endif