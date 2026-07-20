//
// Created by David Sorinola on 09/07/2026.
//

#include "../include/connection.h"

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <memory>
#include <unistd.h>

namespace net {
    RecvData::RecvData(std::string x, int y, bool z) : msg(x), bytesRead(y), closed(z){}

    connection::connection(int handle) {
        this->connectionSocket = handle;
    }

    connection::connection() {
        this->connectionSocket = -1;
    }

    bool connection::valid() {
        return !(this->connectionSocket == -1);
    }

    int connection::connectionSend(const std::string_view msg){
        return send(this->connectionSocket, msg.data(), msg.length(), 0);
    }

    RecvData connection::connectionReceive(int bufferSize) {
        std::unique_ptr<char[]> buffer = std::unique_ptr<char[]>(new char[bufferSize]);
        int bytesRead = recv(this->connectionSocket, buffer.get(), bufferSize, 0);

        switch (bytesRead) {
            case -1:
                return RecvData("",-1,false);
            case 0:
                return RecvData("",0,true);
            default:
                return RecvData(std::string(buffer.get(), bytesRead), bytesRead,false);
        }
    }

    connection::~connection() {
        close(this->connectionSocket);
    }

}
