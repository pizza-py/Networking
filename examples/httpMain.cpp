//
// Created by David Sorinola on 03/08/2026.
//

#include <iostream>
#include <string>
#include "../include/connection.h"
#include "../include/acceptor.h"

int main() {
    net::acceptor myAcceptor = net::acceptor("6767");
    while (true) {
        std::cout << "Waiting for a connection..." << std::endl;
        net::connection client = myAcceptor.acceptConnection();
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
                size_t pos = incoming.msg.find("bababooey");

                std::cout << incoming.msg.substr(0,pos) << std::endl;
            }
        }
    }
    return 0;
}