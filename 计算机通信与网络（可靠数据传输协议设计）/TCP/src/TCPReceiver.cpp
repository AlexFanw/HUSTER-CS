#include "Global.h"
#include "TCPReceiver.h"
TCPReceiver::TCPReceiver():seq(1)
{
    lastAckPkt.acknum = 0;
    lastAckPkt.checksum = 0;
    lastAckPkt.seqnum = -1;
    for(int i = 0; i < Configuration::PAYLOAD_SIZE; i++)
        lastAckPkt.payload[i] = '.';
    lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}


TCPReceiver::~TCPReceiver(){}


void TCPReceiver::receive(const struct Packet & packet)//累计确认
{
    int checkSum = pUtils->calculateCheckSum(packet);//检查发送方发送的报文是否出错
    if(checkSum == packet.checksum && this->seq == packet.seqnum) //如果正确并且为期待接受的报文
    {
        pUtils->printPacket("接收方正确收到报文",packet);
        Message msg;
        memcpy(msg.data, packet.payload, sizeof(packet.payload));
        pns->delivertoAppLayer(RECEIVER,msg);//向上递交给应用层

        this->lastAckPkt.acknum = this->seq + 1;//发送的ack更新期待的序列号
        this->lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);//重新计算校验和
        pUtils->printPacket("接收方向发送方发送确认报文",lastAckPkt);
        pns->sendToNetworkLayer(SENDER,lastAckPkt);//发送ack至网络层
        this->seq ++;//期待的下一个报文序号+1
    }

    else//如果失序或者出错
    {
        if(packet.acknum != seq)
            pUtils->printPacket("ERROR：接收方未正确收到报文：报文序列号错误",packet);

        else
            pUtils->printPacket("ERROR：接收方未正确收到报文：检验和错误",packet);

        pUtils->printPacket("ERROR：接收方发送冗余ACK",this->lastAckPkt);//lastpacket中的acknum为seq的值，即期待接受到的序列号。
        pns->sendToNetworkLayer(SENDER,lastAckPkt);
    }
}