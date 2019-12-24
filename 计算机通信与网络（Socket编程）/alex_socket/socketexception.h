#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H


#pragma once
#include <iostream>
#include <string>
using namespace std;
class SocketException {
public:
    string what() const;
    SocketException();
    SocketException(const string& _msg = string()) :msg(_msg) {}


private:
    string msg;
};

#endif // SOCKETEXCEPTION_H
