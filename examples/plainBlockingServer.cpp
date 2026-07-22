//
// Created by David Sorinola on 08/07/2026.
//

#include "../include/acceptor.h"
#include "../include/connection.h"
#include <iostream>

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
                std::cout << "Received: " << incoming.msg << std::endl;
                std::cout << "Write a response: ";
                std::string outgoingMessage;
                std::getline(std::cin, outgoingMessage);
                std::cout << outgoingMessage;
                std::cout << std::endl;
                client.connectionSend(outgoingMessage + "\n");
            }
        }
    }
    return 0;
}