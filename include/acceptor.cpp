//
// Created by David Sorinola on 08/07/2026.
//

#include "acceptor.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>

namespace net {
    acceptor::acceptor(std::string port) {
        struct addrinfo hints;
        struct addrinfo *res;
        memset(&hints, 0, sizeof(hints));

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = 0;
        hints.ai_flags = AI_PASSIVE;

        int status = getaddrinfo(nullptr, port.c_str(), &hints, &res);

        for (struct addrinfo *cur = res; cur != nullptr; cur = cur->ai_next) {
            int sockfd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);

            std::cout << sockfd << std::endl;
            if (sockfd != -1) {
                int bindStatus = bind(sockfd, cur->ai_addr, cur->ai_addrlen);
                std::cout << bindStatus << std::endl;
                if (bindStatus != -1) {
                    this->acceptorSocket = sockfd;
                    listen(sockfd, 10);
                    return;
                }
            }
            close(sockfd);
        }

        std::cerr << "Failed to bind to socket." << std::endl;
        this->acceptorSocket = -1;
    }

    int acceptor::blockingAccept() {
        struct sockaddr_storage incomingInfo;
        socklen_t incomingInfoSize = sizeof(incomingInfo);
        memset(&incomingInfo, 0, sizeof(incomingInfo));

        int clientSocket = accept(this->acceptorSocket, (sockaddr *) &incomingInfo, &incomingInfoSize);

        if (clientSocket == -1) {
            std::cerr << "Error occured in accepting client" << std::endl;
            return -1;
        } else {
            return clientSocket;
        }
    }

    int acceptor::stop() {
        return close(this->acceptorSocket);
    }
}
