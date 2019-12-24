#ifndef TOOL_H
#define TOOL_H
#include "DataStructure.h"

struct Tool{
	/* 打印Packet的信息*/
	virtual void printPacket(const char * description, const Packet &packet) = 0;
	/*计算一个Packet的校验和*/
	virtual int calculateCheckSum(const Packet &packet) = 0;
	/*产生一个均匀分布的[0-1]间的随机数*/
	virtual double random() = 0;

	virtual ~Tool() = 0;
};

#endif