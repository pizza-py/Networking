//
// Created by David Sorinola on 08/07/2026.
//

#include "../include/acceptor.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include "../include/connection.h"
#include <fcntl.h>

namespace net {
    acceptor::acceptor(const std::string_view port) {
        this->blocking = true;
        addrinfo hints;
        addrinfo *res;
        memset(&hints, 0, sizeof(hints));

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = 0;
        hints.ai_flags = AI_PASSIVE;

        int status = getaddrinfo(nullptr, port.data(), &hints, &res);

        for (addrinfo *cur = res; cur != nullptr; cur = cur->ai_next) {
            int sockfd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);

            std::cout << sockfd << std::endl;
            if (sockfd != -1) {
                int opt = 1;
                setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt , sizeof(opt));
                int bindStatus = bind(sockfd, cur->ai_addr, cur->ai_addrlen);
                std::cout << bindStatus << std::endl;
                if (bindStatus != -1) {
                    this->acceptorSocket = sockfd;
                    listen(sockfd, 10);
                    freeaddrinfo(res);
                    return;
                }
            }
            close(sockfd);
        }

        std::cerr << "Failed to bind to socket." << std::endl;
        this->acceptorSocket = -1;
        freeaddrinfo(res);
    }



    net::connection acceptor::acceptConnection() {
        sockaddr_storage incomingInfo;
        socklen_t incomingInfoSize = sizeof(incomingInfo);
        memset(&incomingInfo, 0, sizeof(incomingInfo));

        int clientSocket = accept(this->acceptorSocket, (sockaddr *) &incomingInfo, &incomingInfoSize);

        if (clientSocket == -1) {
            std::cerr << "Error occured in accepting client" << std::endl;
            return net::connection();
        } else {
            return net::connection(clientSocket);
        }
    }

    bool acceptor::isBlocking() {
        return this->blocking;
    }

    void acceptor::setBlocking(bool setBlockingTo) {
        if (setBlockingTo == true) {
            fcntl(this->acceptorSocket, F_SETFL, 0);
            this->blocking = true;
        } else {
            fcntl(this->acceptorSocket,F_SETFL, O_NONBLOCK);
            this->blocking = false;
        }
    }

    int acceptor::getAcceptorSocket() {
        return this->acceptorSocket;
    }


    acceptor::~acceptor() {
        close(this->acceptorSocket);
    }

}
