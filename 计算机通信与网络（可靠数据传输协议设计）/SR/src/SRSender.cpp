#include "Global.h"
#include "SRSender.h"
SRSender::SRSender():base(0),nextseqnum(0),waitingState(false),num_pac_win(0)
{
}
SRSender::~SRSender()
{
}
bool SRSender::getWaitingState()
{
    return waitingState;
}
bool SRSender::send(const struct Message & message)
{
    if(num_pac_win < len/2)//有空位
    {
        if(num_pac_win == 0)
            for(int i = 0; i<len/2;i++)
                this->cache[i] = 0;//初始化cache

        this->waitingState = false;

        this->win[this->num_pac_win].acknum = -1;
        this->win[this->num_pac_win].seqnum = this->nextseqnum;//分组号0~7
        this->win[this->num_pac_win].checksum = 0;
        memcpy(this->win[this->num_pac_win].payload, message.data, sizeof(message.data));//从应用层获取数据
        this->win[this->num_pac_win].checksum = pUtils->calculateCheckSum(this->win[this->num_pac_win]);//计算检验和

        pUtils->printPacket("发送方发送报文",this->win[this->num_pac_win]);
        pns->startTimer(SENDER,Configuration::TIME_OUT, this->win[this->num_pac_win].seqnum);//每个编号一个计时器
        pns->sendToNetworkLayer(RECEIVER,this->win[this->num_pac_win]);//发送至网络层

        this->num_pac_win ++;//窗口内报文数量加一
        this->nextseqnum = (this->nextseqnum + 1) % len;

        if(this->num_pac_win == len / 2)
            this->waitingState = true;//满了

        return true;
    }

    else//没空位返回 false
    {
        this->waitingState = true;
        return false;
    }
}

void SRSender::receive(const struct Packet & ackPkt)
{
        int sign = 0;
        int check_sum = pUtils->calculateCheckSum(ackPkt);//计算检查和

        if(check_sum == ackPkt.checksum)//正确传输
        {
            int check = 0;
            for(int i = 0; i < num_pac_win ; i++)//遍历发送窗口，有没有ack对应的序号
                if(ackPkt.acknum == win[i].seqnum )
                {
                    cache[i] = 1;
                    sign = i;
                    check = 1;
                }//若发现有对应的seqnum则将cache中对应的窗口下标指示的部分置1

                if(check == 1)
                {
                    if(cache[0] == 1)//如果ack序号为下标
                    {
                        pUtils->printPacket("收到base的ACK",ackPkt);
                        int valid = 0;
                        pns->stopTimer(SENDER,this->win[0].seqnum);//暂停时钟
                        for(int i = 0; i < len/2; i++)//判断从base开始有多少个已经ack了的
                        {
                            if(cache[i] == 0)
                                break;
                            else valid++;
                        }
                        if(valid != this->num_pac_win)
                        {
                            for(int i = 0; i < this->num_pac_win - valid ; i++)
                            {
                                this->win[i] = this->win[i + valid];
                                this->cache[i] = this->cache[i + valid];
                                printf("The current windows's %d number is %d\n",i,win[i].seqnum);
                            }
                            for (int j = this->num_pac_win - valid; j < len/2; j++)
                                cache[j] = 0;
                        }
                        else{
                            for (int i = 0; i < len / 2; i++)
                                cache[i] = 0;
                        }
                        this->num_pac_win = this->num_pac_win - valid;
                        this->base = (this->base + valid) % len;//因为ack中了base，所以base向前移动。
                        this->waitingState = false;
                    }
                    else
                    {
                        pns->stopTimer(SENDER,this->win[sign].seqnum);//收到不是BASE的ACK，只停止时钟
                        pUtils->printPacket("收到窗口内非base的ACK",ackPkt);

                    }
                }
                else
                {
                    pns->stopTimer(SENDER,ackPkt.acknum);
                    pUtils->printPacket("收到窗口之前报文的ACK",ackPkt);
                }
        }else
            pUtils->printPacket("收到ACK包校验和出错",ackPkt);
}


void SRSender::timeoutHandler(int seqNum)
{
    int i = 0;
    while(this->win[i].seqnum != seqNum)//确定发送窗口的第几个超时
        i++;
    pns->stopTimer(SENDER,seqNum);//闹钟关闭
    pUtils->printPacket("发送方定时器超时，重新发送报文段",this->win[i]);
    pns->sendToNetworkLayer(RECEIVER, this->win[i]);//重新发送
    pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);//闹钟重启
}