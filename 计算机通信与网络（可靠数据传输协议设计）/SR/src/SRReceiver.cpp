#include "Global.h"
#include "SRReceiver.h"
SRReceiver::SRReceiver():base(0),num_rcv(0)
{
    Ack.acknum = -1;
    Ack.checksum = 0;
    Ack.seqnum = -1;
    for(int i = 0; i < Configuration::PAYLOAD_SIZE; i++)
        Ack.payload[i] = '.';
    Ack.checksum = pUtils->calculateCheckSum(Ack);
}
SRReceiver::~SRReceiver()
{
}
void SRReceiver::receive(const struct Packet & packet)
{
    if(this->num_rcv == 0) {//若接收方为空则，则将cache中置零
        for (int i = 0; i < len / 2; i++)
            cache[i] = 0;
    }
    int checksum = pUtils->calculateCheckSum(packet);
    if(checksum == packet.checksum )//报文完好
    {
        int check = 0;
        for(int i = 0; i< len/2;i++)//判断序号是否在窗口内部
        {
            if(packet.seqnum == (base + i)% len)
            {
                check = 1;
                break;
            }
        }

        if(check == 1)//若在接收方的窗口以内
        {
            for(int i = 0; i < len/2 ;i++)//遍历接受窗口，看是哪一个序号的packet收到，并判断是否已经缓存
                if(packet.seqnum == (this->base +i)%len) //若找到了对应的序号
                {
                    cache[i] = 1;//标记为已经缓存
                    RcvWin[i] = packet;//将包缓存入接受窗口
                    pUtils->printPacket("接收方正确收到发送方的报文",this->RcvWin[i]);
                    this->Ack.acknum = RcvWin[0].seqnum;
                    this->Ack.checksum = pUtils->calculateCheckSum(Ack);
                    pns->sendToNetworkLayer(SENDER,this->Ack);
                    pUtils->printPacket("接收方发送正确报文",this->RcvWin[i]);
                }

            if(cache[0] == 1)//若收到的报文在BASE
            {
                pUtils->printPacket("接收方正确收到BASE的报文",this->RcvWin[0]);
                int valid = 0;
                for(int i = 0; this->cache[i]!=0 ; i++)//判断从base开始有多少个已经ack了的
                    valid++;
                for(int i = 0;i < valid; i++)//将从发送方窗口数据上交，并且发送ACK
                {
                    Message msg;
                    memcpy(msg.data, this->RcvWin[i].payload, sizeof(this->RcvWin[i].payload));
                    pns->delivertoAppLayer(RECEIVER,msg);
                }
                if(valid != this->num_rcv)//调整窗口
                {
                    for(int i = 0; i < this->num_rcv - valid ; i++)
                    {
                        this->RcvWin[i] = this->RcvWin[i + valid];

                    }

                }
                this->num_rcv = this->num_rcv - valid;//窗口内报文减少valid个
                this->base = (this->base + valid) % len;//因为接受中了base，所以base向前移动。
                for(int i = 0; i < len/2 ; i++)
                    cache[i] = 0;//将cache均置0


            }
        }
        else //若收到的ACK在[base-len/2,base-1]之间，即使已经发送过ACK，依旧发送
        {
            pUtils->printPacket("WARNING:接收方收到发送方的非窗口内的报文",packet);
            this->Ack.acknum = packet.seqnum;
            this->Ack.checksum = pUtils->calculateCheckSum(Ack);
            pns->sendToNetworkLayer(SENDER,this->Ack);//发送ACK
        }
    }

    else
    {
        pUtils->printPacket("ERROR:接收方未正确收到报文:检验和错误",packet);
    }
}