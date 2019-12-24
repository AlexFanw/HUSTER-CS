#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "TCPReceiver.h"
#include "TCPSender.h"
#include <iostream>
int main(int argc, char* argv[])
{
    RdtSender * ps = new TCPSender();
    RdtReceiver * pr = new TCPReceiver();

    pns->setRunMode(1);
    pns->init();
    pns->setRtdSender(ps);
    pns->setRtdReceiver(pr);
    pns->setInputFile("C:\\Users\\AlexFan\\Desktop\\CI\\2\\TCP\\bin\\input.txt");
    pns->setOutputFile("C:\\Users\\AlexFan\\Desktop\\CI\\2\\TCP\\bin\\output.txt");
    pns->start();

    delete ps;
    delete pr;
    delete pUtils;
    delete pns;

    return 0;
}