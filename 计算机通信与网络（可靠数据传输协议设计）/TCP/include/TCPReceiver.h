 #include "RdtReceiver.h"
#ifndef TCP_TCPRECEIVER_H
#define TCP_TCPRECEIVER_H
class TCPReceiver :public RdtReceiver
{
private:
    int seq; //期待收到的下一个报文序号
    Packet lastAckPkt;            //上次发送的确认报文
public:
    TCPReceiver();
    virtual ~TCPReceiver();

public:
    void receive(const Packet &packet); //接受报文，被NetworkService调用
};
#endif
