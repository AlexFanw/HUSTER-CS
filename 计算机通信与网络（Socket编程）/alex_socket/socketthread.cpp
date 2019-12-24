#include "socketthread.h"
#include "config.h"
SocketThread::SocketThread():QThread ()
{

}

void SocketThread::run(){
    tcpServer=new TCPServer(Config::port,Config::ip,5);
    tcpServer->loop();
}



void SocketThread::endThread(){
    tcpServer->close_socket();
}

SocketThread::~SocketThread(){
    delete this->tcpServer;
}
