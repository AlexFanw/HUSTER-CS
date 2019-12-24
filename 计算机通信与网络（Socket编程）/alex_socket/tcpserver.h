#ifndef TCPSERVER_H
#define TCPSERVER_H


#pragma once
#include <map>
#include <list>
#include "tcpsocket.h"
#include "socketexception.h"

class TCPServer : public TCPSocket {
public:
    TCPServer(unsigned short int port, const char *ip = NULL, int backlog = SOMAXCONN) throw(SocketException);

    ~TCPServer();


     int loop();
     bool close_socket();
    //    void accept(SOCKET &client) const throw(SocketException);
    //
    //    SOCKET accept() const throw(SocketException);
private:
     bool endSocket;
};
#endif // TCPSERVER_H
