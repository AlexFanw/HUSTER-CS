#include "RdtSender.h"
#ifndef STOPWAIT_GBNSENDER_H
#define STOPWAIT_GBNSENDER_H
#define len 8
class GBNSender :public RdtSender
{
private:
        int base;//发送窗口的base
        int nextseqnum;//发送窗口的nextseqnum
        bool waitingState;//是否处于等待ACK状态
        Packet win[len];//发送窗口，窗口大小为4
        int num_packet_win;//记录窗口中的报文个数
public:
        bool getWaitingState();
        bool send(const Message &message);//发送应用层下来的Message，被NetworkServiceSimulator调用
        void receive(const Packet &ackPkt);//接受ACK，将被
        void timeoutHandler(int seqNum);

public:
        GBNSender();
        virtual ~GBNSender();
};
#endif //STOPWAIT_GBNSENDER_H
