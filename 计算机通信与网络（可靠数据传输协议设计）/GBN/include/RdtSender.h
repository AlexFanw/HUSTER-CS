#ifndef RDT_SENDER_H
#define RDT_SENDER_H

#include "DataStructure.h"
//定义RdtSender抽象类，规定了必须实现的三个接口方法
//具体的子类比如StopWaitRdtSender、GBNRdtSender必须给出这三个方法的具体实现
//只考虑单向传输，即发送方只发送数据和接受确认
struct  RdtSender
{
	virtual bool send(const Message &message) = 0;						//发送应用层下来的Message，由NetworkService调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待确认状态或发送窗口已满而拒绝发送Message，则返回false
	virtual void receive(const Packet &ackPkt) = 0;						//接受确认Ack，将被NetworkService调用	
	virtual void timeoutHandler(int seqNum) = 0;					//Timeout handler，将被NetworkService调用
	virtual bool getWaitingState() = 0;								//返回RdtSender是否处于等待状态，如果发送方正等待确认或者发送窗口已满，返回true
	virtual ~RdtSender() = 0;
};

#endif
