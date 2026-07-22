//
// Created by David Sorinola on 09/07/2026.
//

#include "../include/connection.h"

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <memory>
#include <unistd.h>
#include <fcntl.h>

namespace net {
    RecvData::RecvData(std::string x, int y, bool z) : msg(x), bytesRead(y), closed(z){}

    connection::connection(int handle) : connectionSocket(handle), blocking(true){}

    connection::connection() : connectionSocket(-1), blocking(true){}

    int connection::getConnectionSocket() {
        return this->connectionSocket;
    }

    bool connection::isBlocking() {
        return this->blocking;
    }

    void connection::setBlocking(bool setBlockingTo) {
        if (setBlockingTo == true) {
            fcntl(this->connectionSocket, F_SETFL, 0);
            this->blocking = true;
        } else {
            fcntl(this->connectionSocket,F_SETFL, O_NONBLOCK);
            this->blocking = false;
        }
    }


    bool connection::valid() { return !(this->connectionSocket == -1);}

    int connection::connectionSend(std::string_view msg){
        int bytesLeft = msg.length();
        int total = msg.length();
        const char* buffer = msg.data();
        int numberSent;
        while (bytesLeft > 0) {
            numberSent = send(this->connectionSocket, buffer + (total-bytesLeft), bytesLeft, 0);
            if (numberSent == -1) {
                return -1;
            } else {
                bytesLeft -= numberSent;
            }
        }
        return total - bytesLeft;
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
