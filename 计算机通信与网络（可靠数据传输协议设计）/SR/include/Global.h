#ifndef GLOBAL_H
#define GLOBAL_H

#include "Tool.h"
#include "NetworkService.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

extern  Tool *pUtils;						//指向唯一的工具类实例，只在main函数结束前delete
extern  NetworkService *pns;				//指向唯一的模拟网络环境类实例，只在main函数结束前delete

#endif