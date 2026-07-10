//
// Created by David Sorinola on 08/07/2026.
//

#include "../include/acceptor.h"
#include "../include/connection.h"
#include <sys/socket.h>
#include <iostream>

int main() {
    net::acceptor myAcceptor = net::acceptor("6767");
    net::connection client = myAcceptor.blockingAccept();
    net::RecvData incoming = client.connectionReceive();

    std::cout << incoming.msg << std::endl;

    std::cout << client.connectionSend("HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "\r\n"
    "You have connected with the bestest most awsomest server in the world!!!\n") << std::endl;

    /*
    char buffer[4096];
    int bytesRead = recv(client.connectionSocket, buffer, sizeof(buffer)-1, 0);

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
        send(client.connectionSocket, response, bytesRead+1, 0);
    }
    */
    return 0;
}