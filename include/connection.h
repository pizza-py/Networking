//
// Created by David Sorinola on 09/07/2026.
//

#ifndef NETWORKING_CONNECTION_H
#define NETWORKING_CONNECTION_H

#include <string>
namespace net {
    struct RecvData {
    public: std::string msg;
        int bytesRead;
        bool closed;

        RecvData(std::string, int, bool);
    };
    class connection {
    private:
        int connectionSocket;
        bool blocking;

    public:

        connection(int handle);

        connection();

        int getConnectionSocket();

        bool isBlocking();

        void setBlocking(bool);

        bool valid();

        int connectionSend(std::string_view msg);

        RecvData connectionReceive(int bufferSize=4096);

        ~connection();
    };
} // net

#endif //NETWORKING_CONNECTION_H