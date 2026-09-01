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
        std::string buffer;


    public:

        connection(int handle);

        connection();

        int getConnectionSocket();

        void setConnectionSocket(int);

        bool isBlocking();

        void setBlocking(bool);

        bool valid();

        int connectionSend(std::string msg);

        RecvData connectionReceive(int bufferSize=4096);

        std::string getBuffer();

        void addToBuffer(std::string);

        void clearBuffer();

        connection(const connection&) = delete;

        connection& operator=(const connection&) = delete;

        connection(connection&&);

        connection& operator=(connection&&);

        ~connection();
    };
} // net

#endif //NETWORKING_CONNECTION_H