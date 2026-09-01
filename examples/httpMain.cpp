//
// Created by David Sorinola on 03/08/2026.
//

#include <iostream>
#include <string>
#include "../include/connection.h"
#include "../include/acceptor.h"
#include "../include/parsing.h"
#include "../include/response.h"

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
                incoming.msg.erase(incoming.msg.end()-4, incoming.msg.end());
                http::HTTPRequest myRequest = http::parseHTTP(incoming.msg);
                if (!myRequest.getValid()) {
                    std::cerr << "Failed to Parse HTTP. Error code: " << myRequest.getFailCode() << std::endl;
                } else {
                    std::cout << "Formulating response:" << std::endl;
                    http::response myResponse = http::response();
                    myResponse.setServer("My awsome server");
                    myResponse.setContent("Super califragilistics expialadocious");
                    std::cout << "Made the response object!" << std::endl;
                    std::cout << "Sending: "<<  myResponse.buildResponse() << std::endl;
                    client.connectionSend(myResponse);
                }
            }
        }
    }
    return 0;
}