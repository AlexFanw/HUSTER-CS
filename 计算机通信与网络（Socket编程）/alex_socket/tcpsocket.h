
#include<iostream>
#include <winsock2.h>
#include <string>



const int MAXCONNECTION = 5;
const int MAXRECEIVE = 500;

class TCPSocket {
protected:
    SOCKET socket;
    bool close();

    bool isValid() const {
        return (this->socket != -1);
    }
    TCPSocket();

    ~TCPSocket();

    bool create();

    bool bind(unsigned short int port, const char *ip = NULL) const;

    bool listen(int backlog);

    //bool accept(SOCKET &clientSocket) const;

    bool connect(unsigned short int port, const char *ip) const;


private:
    //    SOCKET socket;
};


