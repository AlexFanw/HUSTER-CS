#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H
#include<QThread>
#include"tcpserver.h"
class SocketThread:public QThread
{

public:
    SocketThread();
    ~SocketThread();
    void run();
    void endThread();
private:
    TCPServer* tcpServer;

};

#endif // SOCKETTHREAD_H
