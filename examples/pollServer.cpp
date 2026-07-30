//
// Created by David Sorinola on 21/07/2026.
//

#include "../include/acceptor.h"
#include "../include/connection.h"
#include <poll.h>
#include <vector>
#include <iostream>
#include <utility>

void addConnection(std::vector<pollfd>& fds, net::acceptor& myAcceptor, std::vector<net::connection>& connections) {
    net::connection connection = myAcceptor.acceptConnection();
    connection.setBlocking(false);
    std::cout << "Added connection: " << connection.getConnectionSocket() << std::endl;
    pollfd connectionPollFd = pollfd();
    connectionPollFd.events = POLLIN | POLLHUP;
    connectionPollFd.fd = connection.getConnectionSocket();
    fds.push_back(connectionPollFd);
    connections.push_back(std::move(connection));
}

int handleClient(std::vector<pollfd>& fds, std::vector<net::connection>& connections, int connectionIndex) {
    net::RecvData incoming = connections[connectionIndex].connectionReceive();
    if (incoming.closed) {
        std::cout << "A connection closed!" << std::endl;
        fds.erase(fds.begin()+connectionIndex+1);
        connections.erase(connections.begin()+connectionIndex);
        return 1;
    } else {
        std::cout << "Received data:" << std::endl << incoming.msg << "Sending to all connections..." << std::endl;
        for (int i=0;i<connections.size();i++) {
            if (i != connectionIndex) {
                connections[i].connectionSend(incoming.msg);
            }
        }
        return 0;
    }
}

void handleEvents(std::vector<pollfd>& fds, net::acceptor& myAcceptor, std::vector<net::connection>& connections) {
    for (int i=0; i<fds.size();i++) {
        pollfd cur = fds.at(i);
        if (cur.revents & (POLLIN | POLLHUP)) {
            if (cur.fd == myAcceptor.getAcceptorSocket()) {
                addConnection(fds, myAcceptor, connections);
            } else {
                 i -= handleClient(fds, connections, i-1);
            }
        }
    }
}

int main() {
    std::vector<pollfd> fds = std::vector<pollfd>();
    std::vector<net::connection> connections = std::vector<net::connection>();
    net::acceptor myAcceptor = net::acceptor("6767");
    myAcceptor.setBlocking(false);

    pollfd listener = pollfd();
    listener.events = POLLIN;
    listener.fd = myAcceptor.getAcceptorSocket();
    fds.push_back(listener);

    while (true) {
        std::cout << "Waiting for event to happen..." << std::endl;
        int numEvents = poll(fds.data(), fds.size(), -1);
        std::cout << "Something happened!" << std::endl;
        if (numEvents == -1) {
            std::cerr << "Error occured while polling" << std::endl;
            return 1;
        } else {
            handleEvents(fds,myAcceptor, connections);
        }
    }
    return 0;
}