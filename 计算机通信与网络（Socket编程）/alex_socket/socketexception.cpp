#include "SocketException.h"
#include <cstring>
#pragma warning(disable:4996)

string SocketException::what() const {
    if (errno == 0)
        return "Socket Exception" + msg;
    return "Socket Exception" + msg + strerror(errno);
}
