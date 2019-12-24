#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#pragma warning (disable: 4786)
#pragma warning(disable:4996)
#include<map>
#include<string>
#include<ctime>
#include<iostream>
#include<config.h>
#include<global.h>
#include<qdebug.h>
using namespace std;

bool ParseRequest(string szRequest, string &szResponse, bool &bKeepAlive);

BOOL writeToSocket(SOCKET s, const char *buff, int count)
{
    int sendCount, currentPosition = 0;
    while (count > 0 && (sendCount = send(s, buff + currentPosition, count, 0)) != SOCKET_ERROR)
    {
        count -= sendCount;
        currentPosition += sendCount;
    }
    if (sendCount == SOCKET_ERROR)return FALSE;
    return TRUE;
}


BOOL writeToSocket(SOCKET s, char *pszBuff)
{
    return writeToSocket(s, pszBuff, strlen(pszBuff));
}

DWORD WINAPI HttpThread(
      LPVOID lpParameter
)
{

    SOCKET clientSocket = (SOCKET)lpParameter;
    char recvBuf[20480];
    bool bkeepalive = true;
    // Loop as long as the connection is opened.
    while (bkeepalive)
    {
        int count = recv(clientSocket, recvBuf, 20480, 0);
        if (count == 0)break;//
        if (count == SOCKET_ERROR)break;//count<0
        //if(count>0)
        recvBuf[count] = 0;

        string szRequest(recvBuf);
        string szResponse;
        bkeepalive = false;
        ParseRequest(szRequest, szResponse, bkeepalive);
        writeToSocket(clientSocket, szResponse.c_str(), (int)szResponse.length());

        pthread_mutex_lock(&(Global::sMutex));

            sockaddr_in clientAddr;
            int nameLen,rtn;
            QString clientAddress;
            nameLen = sizeof(clientAddr);
            rtn = getsockname(clientSocket,(LPSOCKADDR)&clientAddr,&nameLen);
            closesocket(clientSocket);
            if(rtn != SOCKET_ERROR){
                clientAddress += QString::fromStdString(inet_ntoa(clientAddr.sin_addr));
            }
            int n;
            QString szMethod;
            QString szFileName;
            QString szStatusCode;

            //
            // Check Method
            //
            n = szRequest.find(" ", 0);
            if (n != string::npos)
            {
                szMethod = QString::fromStdString(szRequest.substr(0, n));
                if (szMethod == "GET")
                {
                    // Get file name
                    int n1 = szRequest.find(" ", n + 1);
                    if (n != string::npos)
                    {
                        szFileName = QString::fromStdString(szRequest.substr(n + 1, n1 - n - 1));
                        if (szFileName == "/")
                        {
                            szFileName = "/index.html";
                        }
                    }
                    FILE* f;
                    if((f=fopen((Config::tableOfFiles.toStdString() + szFileName.toStdString()).c_str(), "r+b"))!=NULL)
                    {
                        szStatusCode = "200 OK";
                        fclose(f);
                    }
                    else{
                        szStatusCode= "404 Not Found";
                    }
                }
                else
                {
                    szStatusCode = "501 Not Implemented";

                }
            }
            char szDT[128];
            struct tm *newtime;
            time_t ltime;

            time(&ltime);
            newtime = localtime(&ltime);
            strftime(szDT, 128,
                "%Y %d %b %H:%M:%S", newtime);

            qDebug("ip: %s",qPrintable(clientAddress));
            Global::item=new QStandardItem(clientAddress);
            Global::model->setItem(Global::i,0,Global::item);
            Global::item=new QStandardItem(szFileName);
            Global::model->setItem(Global::i,1,Global::item);
            Global::item=new QStandardItem(szStatusCode);
            Global::model->setItem(Global::i,2,Global::item);
            Global::item=new QStandardItem(QString::fromStdString(szDT));
            Global::model->setItem(Global::i,3,Global::item);
            Global::i++;

        pthread_mutex_unlock(&(Global::sMutex));
    }

//    closesocket(clientSocket);
    int id=GetCurrentThreadId();
    std::cout<<"thread"<<id<<"exit"<<std::endl;
    return 0;
}

typedef map<string, string>				MIMETYPES;
MIMETYPES  MimeTypes;
string m_HomeDir;
string m_DefIndex;
#define ERROR404 "404.html"
#define ERROR501 "501.html"
#define SERVERNAME "localhost"


void Init()
{

    m_HomeDir = (string)(const char *)Config::tableOfFiles.toLocal8Bit();
    m_DefIndex = "index.html";

    if (m_HomeDir.substr(m_HomeDir.size() - 1, 1) != "\\")
        m_HomeDir += "\\";
    //
    // Init MIME Types
    //
    MimeTypes["doc"] = "application/msword";
    MimeTypes["bin"] = "application/octet-stream";
    MimeTypes["dll"] = "application/octet-stream";
    MimeTypes["exe"] = "application/octet-stream";
    MimeTypes["pdf"] = "application/pdf";
    MimeTypes["gz"] = "application/x-gzip";
    MimeTypes["class"] = "application/x-java-class";
    MimeTypes["js"] = "application/x-javascript";
    MimeTypes["zip"] = "application/zip";
    MimeTypes["mp3"] = "audio/mpeg";
    MimeTypes["vox"] = "audio/voxware";
    MimeTypes["wav"] = "audio/wav";
    MimeTypes["mp4"] = "video/mp4";
    MimeTypes["ra"] = "audio/x-pn-realaudio";
    MimeTypes["ram"] = "audio/x-pn-realaudio";
    MimeTypes["bmp"] = "image/bmp";
    MimeTypes["gif"] = "image/gif";
    MimeTypes["jpeg"] = "image/jpeg";
    MimeTypes["jpg"] = "image/jpeg";
    MimeTypes["tif"] = "image/tiff";
    MimeTypes["tiff"] = "image/tiff";
    MimeTypes["htm"] = "text/html";
    MimeTypes["html"] = "text/html";
    MimeTypes["c"] = "text/plain";
    MimeTypes["cpp"] = "text/plain";
    MimeTypes["def"] = "text/plain";
    MimeTypes["h"] = "text/plain";
    MimeTypes["txt"] = "text/plain";
    MimeTypes["rtx"] = "text/richtext";
    MimeTypes["rtf"] = "text/richtext";
    MimeTypes["java"] = "text/x-java-source";
    MimeTypes["css"] = "text/css";

}



bool ParseRequest(string szRequest, string &szResponse, bool &bKeepAlive)
{
    //
    // Simple Parsing of Request
    //
    string szMethod;
    string szFileName;
    string szFileExt;
    string szStatusCode("200 OK");
    string szContentType("text/html");
    string szConnectionType("close");
    string szNotFoundMessage;
    string szDateTime;
    char pResponseHeader[2048];
    fpos_t lengthActual = 0, length = 0;
    char *pBuf = NULL;
    int n;

    //
    // Check Method
    //
    n = szRequest.find(" ", 0);
    if (n != string::npos)
    {
        szMethod = szRequest.substr(0, n);
        if (szMethod == "GET")
        {
            //
            // Get file name
            //
            int n1 = szRequest.find(" ", n + 1);
            if (n != string::npos)
            {
                szFileName = szRequest.substr(n + 1, n1 - n - 1);
                if (szFileName == "/")
                {
                    szFileName = m_DefIndex;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            szStatusCode = "501 Not Implemented";
            szFileName = ERROR501;
        }
    }
    else
    {
        return false;
    }

    //
    // Determine Connection type
    //
    n = szRequest.find("\nConnection: Keep-Alive", 0);
    if (n != string::npos)
        bKeepAlive = true;

    //
    // Figure out content type
    //
    int nPointPos = szFileName.rfind(".");
    if (nPointPos != string::npos)
    {
        szFileExt = szFileName.substr(nPointPos + 1, szFileName.size());
        strlwr((char*)szFileExt.c_str());
        MIMETYPES::iterator it;
        it = MimeTypes.find(szFileExt);
        if (it != MimeTypes.end())
            szContentType = (*it).second;
    }

    //
    // Obtain current GMT date/time
    //
    char szDT[128];
    struct tm *newtime;
    time_t ltime;

    time(&ltime);
    newtime = gmtime(&ltime);
    strftime(szDT, 128,"%H:%M:%S", newtime);

    //
    // Read the file
    //
    FILE *f;
    f = fopen((m_HomeDir + szFileName).c_str(), "r+b");
    if (f != NULL)
    {
        // Retrive file size
        fseek(f, 0, SEEK_END);
        fgetpos(f, &lengthActual);
        fseek(f, 0, SEEK_SET);

        pBuf = new char[lengthActual + 1];

        length = fread(pBuf, 1, lengthActual, f);
        fclose(f);

        //
        // Make Response
        //
        sprintf(pResponseHeader, "HTTP/1.0 %s\r\nDate: %s\r\nServer: %s\r\nAccept-Ranges: bytes\r\nContent-Length: %d\r\nConnection: %s\r\nContent-Type: %s\r\n\r\n",
            szStatusCode.c_str(), szDT, SERVERNAME, (int)length, bKeepAlive ? "Keep-Alive" : "close", szContentType.c_str());
    }
    else
    {
        //
        // In case of file not found
        //
        if (szFileName == ERROR501)
        {
            szNotFoundMessage = "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head>"
                "<body><h2>Casper Simple Web Server</h2><div>501 - Method Not Implemented</div></body></html>";
        }
        else
        {
            f = fopen((m_HomeDir + ERROR404).c_str(), "r+b");
            if (f != NULL)
            {
                // Retrive file size
                fseek(f, 0, SEEK_END);
                fgetpos(f, &lengthActual);
                fseek(f, 0, SEEK_SET);
                pBuf = new char[lengthActual + 1];
                length = fread(pBuf, 1, lengthActual, f);
                fclose(f);
                szNotFoundMessage = string(pBuf, length);
                delete pBuf;
                pBuf = NULL;
            }
            else szNotFoundMessage = "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head>"
                "<body><h2>Casper Simple Web Server</h2><div>404 - Not Found</div></body></html>";
            szStatusCode = "404 Resource not found";
        }

        sprintf(pResponseHeader, "HTTP/1.0 %s\r\nContent-Length: %d\r\nContent-Type: text/html\r\nDate: %s\r\nServer: %s\r\n\r\n%s",
            szStatusCode.c_str(), szNotFoundMessage.size(), szDT, SERVERNAME, szNotFoundMessage.c_str());
        bKeepAlive = false;
    }

    szResponse = string(pResponseHeader);
    if (pBuf)
        szResponse += string(pBuf, length);
    delete pBuf;
    pBuf = NULL;


    return false;
}
