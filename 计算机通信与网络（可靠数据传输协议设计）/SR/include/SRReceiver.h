#ifndef STOPWAIT_SRRECEIVER_H
#define STOPWAIT_SRRECEIVER_H
#include "RdtReceiver.h"
#define len 8
class SRReceiver :public RdtReceiver
{
private:
        Packet RcvWin[len/2];
        int base;
        Packet Ack;
        int num_rcv;
        int cache[len/2];//标记接受方窗口内那些ack已经收到
public:
        SRReceiver();
        virtual ~SRReceiver();

public:
        void receive(const Packet &packet);
};
#endif
