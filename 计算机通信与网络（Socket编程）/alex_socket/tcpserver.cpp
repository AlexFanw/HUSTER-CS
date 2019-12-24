#include "TCPServer.h"
#include<vector>
#include<fstream>
#include<windows.h>
#include<QDebug>
#pragma warning(disable:4996)

extern
DWORD WINAPI HttpThread(
   LPVOID lpParameter
);
extern void Init();

using namespace std;

TCPServer::TCPServer(unsigned short int port, const char *ip, int backlog)
throw(SocketException) {
    if (!create()) {
        cout << "socket create error" << endl;
        throw SocketException("socket create error");
    }
    cout << "create success" <<endl;
    if (!bind(port, ip)) {
        cout << "socket bind error" << endl;
    //    throw SocketException("socket bind error");
        std::cout<<"port error"<<std::endl;
        return;
    }
    cout << "bind success" << endl;
    if (!listen(backlog)) {
        cout << "socket listen error" << endl;
        throw SocketException("socket listen error");
    }
    cout << "listen success" << endl;
    this->endSocket=false;
    cout << "server initial success" << endl;
};

TCPServer::~TCPServer() {



    //关闭所有会话socket并释放会话队列


};

int TCPServer::loop() {
    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);
    //以一个无限循环的方式，不停地接收客户端socket连接
    Init();
    std::cout<<"init "<<std::endl;
    while (!this->endSocket)
    {
        //请求到来后，接受连接请求，返回一个新的对应于此次连接的套接字
        SOCKET AcceptSocket = accept(socket, (SOCKADDR*)&addrClient, &len);
        if (AcceptSocket == INVALID_SOCKET)break; //出错
        std::cout<<"accept socket success"<<std::endl;
        //启动线程
        DWORD dwThread;
        HANDLE hThread = CreateThread(NULL, 0, HttpThread, (LPVOID)AcceptSocket, 0, &dwThread);
        if (hThread == NULL)
        {
            closesocket(AcceptSocket);
            wprintf(L"Thread Creat Failed!\n");
            break;
        }
        CloseHandle(hThread);
//        WaitForSingleObject(hThread,);
    }
    qDebug("close socket");
    std::cout<<"aaaa"<<std::endl;
    closesocket(socket);
    WSACleanup();
    return 0;
}


bool TCPServer::close_socket(){
    this->endSocket=true;
    closesocket(socket);
    WSACleanup();
    qDebug("endSocket");
}
