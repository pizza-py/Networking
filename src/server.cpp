//
// Created by David Sorinola on 08/07/2026.
//

#include "../include/acceptor.h"
#include "../include/connection.h"
#include <sys/socket.h>
#include <iostream>

int main() {
    net::acceptor myAcceptor = net::acceptor("6767");
    while (true) {
        std::cout << "Waiting for a connection..." << std::endl;
        net::connection client = myAcceptor.blockingAccept();
        std::cout << "Connected!" << std::endl;
        bool stayInLoop = true;
        while (stayInLoop) {
            std::cout << "Waiting for data to be received" << std::endl;
            net::RecvData incoming = client.connectionReceive();
            std::cout << "Received data!" << std::endl;
            if (incoming.closed) {
                std::cout << "The connection closed." << std::endl;
                stayInLoop = false;
            } else {
                std::cout << incoming.msg << std::endl;
                client.connectionSend("HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/plain\r\n"
                    "\r\n"
                    "You have connected with the bestest most awsomest server in the world!!!\r\n");
                std::cout << "Sent a cool resposne" << std::endl;
            }
        }
    }
    return 0;
}