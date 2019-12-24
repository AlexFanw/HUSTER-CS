#ifndef NETWORK_SERVICE_H
#define NETWORK_SERVICE_H

#include "RandomEventEnum.h"
#include "RdtSender.h"
#include "RdtReceiver.h"


//定义NetworkService抽象类，规定了学生实现的RdtSender和RdtReceiver可以调用的的接口方法
struct  NetworkService {

	virtual void startTimer(RandomEventTarget target, int timeOut,int seqNum) = 0;	//发送方启动定时器，由RdtSender调用
	virtual void stopTimer(RandomEventTarget target,int seqNum) = 0;				//发送方停止定时器，由RdtSender调用
	virtual void sendToNetworkLayer(RandomEventTarget target, Packet pkt) = 0;		//将数据包发送到网络层，由RdtSender或RdtReceiver调用
	virtual void delivertoAppLayer(RandomEventTarget target, Message msg) = 0;		//将数据包向上递交到应用层，由RdtReceiver调用

	virtual void init() = 0;														//初始化网络环境，在main里调用
	virtual void start() = 0;														//启动网络环境，在main里调用
	virtual void setRtdSender(RdtSender *ps) = 0;									//设置具体的发送方对象
	virtual void setRtdReceiver(RdtReceiver *ps) = 0;								//设置具体的发送方对象
	virtual void setInputFile(const char *ifile) = 0;								//设置输入文件路径
	virtual void setOutputFile(const char *ofile) = 0;								//设置输出文件路径
	virtual ~NetworkService() = 0;
	virtual void setRunMode(int mode = 0) = 0;										//设置运行模式，0：VERBOSE模式，1：安静模式
};

#endif
