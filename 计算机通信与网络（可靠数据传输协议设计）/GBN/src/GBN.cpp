#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "GBNReceiver.h"
#include "GBNSender.h"
#include <iostream>
int main(int argc, char* argv[])
{
    RdtSender * ps = new GBNSender();
    RdtReceiver * pr = new GBNReceiver();
    pns->setRunMode(1);
    pns->init();
    pns->setRtdSender(ps);
    pns->setRtdReceiver(pr);
    pns->setInputFile("C:\\Users\\AlexFan\\Desktop\\CI\\2\\GBN\\bin\\input.txt");
    pns->setOutputFile("C:\\Users\\AlexFan\\Desktop\\CI\\2\\GBN\\bin\\output.txt");
    pns->start();
    delete ps;
    delete pr;
    delete pUtils;
    delete pns;

    return 0;
}