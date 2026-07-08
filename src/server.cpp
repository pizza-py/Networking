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

int main() {
    net::acceptor myAcceptor = net::acceptor("6768");
    int client = myAcceptor.blockingAccept();

    char buffer[4096];
    int bytesRead = recv(client, buffer, sizeof(buffer)-1, 0);

    if (bytesRead == -1) {
        std::cout << "Error occurred in reading packets" << std::endl;
        return 5;
    } else {
        buffer[bytesRead] = '\0';
        std::cout << "Received: " << std::endl;
        const char response[] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Length: 13\r\n"
    "Content-Type: text/plain\r\n"
    "\r\n"
    "Hello, world!";
        send(client, response, bytesRead+1, 0);
    }
    close(client);
    myAcceptor.stop();
    return 0;
}