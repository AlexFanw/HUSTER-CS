#include "Global.h"
#include "GBNSender.h"
GBNSender::GBNSender():base(1),nextseqnum(1),waitingState(false),num_packet_win(0)
{
}
GBNSender::~GBNSender()
{
}
bool GBNSender::getWaitingState()
{
        return waitingState;
}
bool GBNSender::send(const struct Message & message)
{
    if(nextseqnum < base + len)//还可以继续发送报文
    {
        this->waitingState = false;//标记此时窗口未满
        this->win[num_packet_win].acknum = -1;//ack置为-1
        this->win[num_packet_win].seqnum = this->nextseqnum;//指向下一个报文
        this->win[num_packet_win].checksum = 0;//检查和置0
        memcpy(this->win[num_packet_win].payload, message.data, sizeof(message.data));//拷贝数据

        this->win[num_packet_win].checksum = pUtils->calculateCheckSum(this->win[num_packet_win]);//计算检查和
        pUtils->printPacket("发送方发送报文",this->win[num_packet_win]);
        if(base == nextseqnum)//若为窗口首元素则打开计时器
            pns->startTimer(SENDER, Configuration::TIME_OUT, this->win[num_packet_win].seqnum);

        pns->sendToNetworkLayer(RECEIVER, this->win[num_packet_win]);//发送报文至网络层
        this->num_packet_win++;//窗口内packet数目+1

        if(num_packet_win > len)//判断窗口是否满
            this->waitingState = true;//窗口满了！

        this->nextseqnum++;//发送下一个组
        return true;
    }
    else
    {
        this->waitingState = true;
        return false;
    }
}
void GBNSender::receive(const struct Packet & ack)//接受确认ack
{
    if(this->num_packet_win > 0 )//窗口报文数大于0
    {
        int checkSum = pUtils->calculateCheckSum(ack);//计算检查和

        if(checkSum == ack.checksum && ack.acknum >= this->base)//累计确认
        {
            int num = ack.acknum - this->base + 1;//记录下收到的ack序号例如base=1， ack1丢失但是收到了ack2，也可以算ack1收到了

            base = ack.acknum + 1;//重新设置base
            pUtils->printPacket("发送方收到正确确认", ack);

            if(this->base == this->nextseqnum)
                pns->stopTimer(SENDER, this->win[0].seqnum);//结束则停止
            else//不然就重启计时器
            {
                pns->stopTimer(SENDER, this->win[0].seqnum);
                pns->startTimer(SENDER,Configuration::TIME_OUT,this->win[num].seqnum);
            }

            for(int i = 0; i < num_packet_win - num ; i++)
            {
                win[i] = win[i+num];//将窗口内的packet向前移动num位
                printf("The current windows's %d number is %d\n",i,win[i].seqnum);
            }


            this->num_packet_win = this->num_packet_win - num;//窗口向前移动num，即窗口内的packet数目减去num
        }
    }
}
void GBNSender::timeoutHandler(int seqNum)
{
    pUtils->printPacket("发送方定时器时间到，重发上一次发送的报文",this->win[0]);
    pns->stopTimer(SENDER,this->win[0].seqnum);
    pns->startTimer(SENDER, Configuration::TIME_OUT,this->win[0].seqnum);
    for(int i = 0; i < num_packet_win; i++)
    {
        pns->sendToNetworkLayer(RECEIVER, this->win[i]);
    }

}

