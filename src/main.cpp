//
// Created by David Sorinola on 01/07/2026.
//
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Could not create a socket." << std::endl;
        return 1;
    }

    struct sockaddr_in socketConfig;
    memset(&socketConfig, 0, sizeof(socketConfig));

    socketConfig.sin_family = AF_INET;
    socketConfig.sin_port = htons(6767);
    inet_pton(AF_INET, "127.0.0.1", &socketConfig.sin_addr);

    int success = bind(server_socket, (sockaddr*) &socketConfig, sizeof(socketConfig));

    if (success == -1) {
        std::cerr << "Could not bind socket to Port/IP" << std::endl;
        return 2;
    }

    int isListening = listen(server_socket, 10);

    if (isListening == -1) {
        std::cerr << "Could not get the thing to listen" << std::endl;
        return 3;
    }

    struct sockaddr_storage incomingInfo;
    socklen_t incomingInfoSize = sizeof(incomingInfo);
    memset(&incomingInfo, 0, sizeof(incomingInfo));


    int clientSocket = accept(server_socket, (sockaddr*) &incomingInfo, &incomingInfoSize);

    if (clientSocket == -1) {
        std::cerr << "Invalid socket" << std::endl;
        return 4;
    }

    char buffer[4096];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer)-1, 0);

    if (bytesRead == -1) {
        std::cout << "Error occurred in reading packets" << std::endl;
        return 5;
    } else {
        buffer[bytesRead] = '\0';
        std::cout << "Received: " << buffer << std::endl;
        send(clientSocket, "makmsdlmsaldmklwamm sdaslmflsdf", bytesRead+1, 0);
    }
    close(server_socket);
    close(clientSocket);
    return 0;
}