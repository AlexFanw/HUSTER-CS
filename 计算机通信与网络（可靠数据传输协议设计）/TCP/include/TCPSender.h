#include "RdtSender.h"
#ifndef TCP_TCPSENDER_H
#define TCP_TCPSENDER_H
#define len 8
class TCPSender :public RdtSender
{
private:
    int base;//发送窗口的base
    int nextseqnum;//发送窗口的nextseqnum
    bool waitingState;//是否处于等待ACK状态
    Packet win[len];//发送窗口，窗口大小为4
    int num_pac_win;//记录窗口中的报文个数
    int count;
    int current_rcv_ack;
    int last_rcv_ack;
public:
    bool getWaitingState();
    bool send(const Message &message);//发送应用层下来的Message，被NetworkServiceSimulator调用
    void receive(const Packet &ackPkt);//接受ACK，将被
    void timeoutHandler(int seqNum);

public:
    TCPSender();
    virtual ~TCPSender();
};
#endif //TCP_TCPSENDER_H
