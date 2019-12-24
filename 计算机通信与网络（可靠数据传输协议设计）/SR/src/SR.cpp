#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "SRReceiver.h"
#include "SRSender.h"
#include <iostream>
int main(int argc, char* argv[])
{
    RdtSender * ps = new SRSender();
    RdtReceiver * pr = new SRReceiver();
    pns->setRunMode(1);
    pns->init();
    pns->setRtdSender(ps);
    pns->setRtdReceiver(pr);
    pns->setInputFile("C:\\Users\\AlexFan\\Desktop\\CI\\2\\SR\\bin\\input.txt");
    pns->setOutputFile("C:\\Users\\AlexFan\\Desktop\\CI\\2\\SR\\bin\\output.txt");
    pns->start();
    delete ps;
    delete pr;
    delete pUtils;
    delete pns;

    return 0;
}