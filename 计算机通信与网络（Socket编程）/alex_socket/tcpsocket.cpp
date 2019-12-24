#include <inaddr.h>
#include "TCPSocket.h"

#pragma warning(disable:4996)

TCPSocket::TCPSocket() : socket(-1) {

}


TCPSocket::~TCPSocket() {
    if (!isValid())
        ::closesocket(socket);
    WSACleanup();
}

bool TCPSocket::create() {
    if (isValid())
        return false;
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    if ((socket = ::socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        WSACleanup();
        return false;
    }
    return true;
}


bool TCPSocket::bind(unsigned short int port, const char *ip) const {
    if (!isValid())
        return false;
    sockaddr_in addr;

    ZeroMemory((char *)&addr, sizeof(sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (ip == NULL)
        addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    else
        addr.sin_addr.S_un.S_addr = inet_addr(ip);
    if (::bind(socket, (const sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(socket);
        WSACleanup();
        return false;
    }
    return true;
}


bool TCPSocket::listen(int backlog) {
    if (!isValid())
        return false;
    if (::listen(socket, backlog) == SOCKET_ERROR) {
        closesocket(socket);
        WSACleanup();
        return false;
    }
    return true;
}

//bool TCPSocket::accept(SOCKET &clientSocket) const {
//	if (!isValid())
//	/	return false;
//	clientSocket = ::accept(this->socket, NULL, NULL);
//	if (clientSocket == SOCKET_ERROR)
//		return false;
//	return true;
//}


bool TCPSocket::connect(unsigned short int port, const char *ip) const {
    if (!isValid())
        return false;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.S_un.S_addr = inet_addr(ip);
    if (::connect(socket, (const sockaddr *)&addr, sizeof(addr)) == -1)
        return false;
    return true;
}

bool TCPSocket::close() {
    if (isValid())
        return false;
    ::closesocket(socket);
    socket = -1;
    return true;
}

