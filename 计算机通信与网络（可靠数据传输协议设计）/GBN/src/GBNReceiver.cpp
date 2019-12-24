#include "Global.h"
#include "GBNReceiver.h"
GBNReceiver::GBNReceiver():seq(1)
{
    lastAckPkt.acknum = 0;
    lastAckPkt.checksum = 0;
    lastAckPkt.seqnum = -1;
    for(int i = 0; i < Configuration::PAYLOAD_SIZE; i++)
        lastAckPkt.payload[i] = '.';
    lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}
GBNReceiver::~GBNReceiver()
{
}
void GBNReceiver::receive(const struct Packet & packet)
{
    int checkSum = pUtils->calculateCheckSum(packet);//计算检查和

    if(checkSum == packet.checksum && this->seq == packet.seqnum)//收到了正确序号的报文
    {
        pUtils->printPacket("接收方正确收到发送方的报文",packet);
        Message msg;
        memcpy(msg.data, packet.payload, sizeof(packet.payload));//上交文件至应用层
        pns->delivertoAppLayer(RECEIVER,msg);//上交

        lastAckPkt.acknum = packet.seqnum;//准备发回ack
        lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);//计算ackpackage检查和

        pUtils->printPacket("接收方发送确认报文",lastAckPkt);
        pns->sendToNetworkLayer(SENDER,lastAckPkt);//发送ack给发送方

        this->seq ++;
    }

    else//如果检查和错误，或者乱序
    {
        if(packet.acknum != seq)//如果乱序
            pUtils->printPacket("ERROR：接收方未收到正确报文：报文序号错误",packet);
        else
            pUtils->printPacket("ERROR：接收方未收到正确报文：检验和错误",packet);

        pUtils->printPacket("接受方重新发送上次的确认报文",lastAckPkt);//发送上一次的确认报文
        pns->sendToNetworkLayer(SENDER,lastAckPkt);//发送上一次的确认报文

    }
}