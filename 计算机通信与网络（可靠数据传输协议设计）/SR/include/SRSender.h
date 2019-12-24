#ifndef STOPWAIT_SRSENDER_H
#define STOPWAIT_SRSENDER_H
#include "RdtSender.h"
#define len 8 //
class SRSender :public RdtSender
{
private:
        int base;//窗口初始段
        int nextseqnum;//下一个报文
        bool waitingState;
        int num_pac_win;
        int cache[len/2];//发送窗口中已经被缓存的报文序号
        Packet win[len/2];
public:
        bool getWaitingState();
        bool send(const Message &message);//发送应用层下来的Message，被NetworkServiceSimulator调用
        void receive(const Packet &ackPkt);//接受ACK，将被
        void timeoutHandler(int seqNum);

public:
        SRSender();
        virtual  ~SRSender();
};
#endif //STOPWAIT_SRSENDER_H
