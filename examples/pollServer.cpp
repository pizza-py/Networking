//
// Created by David Sorinola on 21/07/2026.
//

#include "../include/acceptor.h"
#include "../include/connection.h"
#include <poll.h>
#include <vector>
#include <iostream>

void addConnection(std::vector<pollfd>& fds, net::acceptor& myAcceptor, std::vector<net::connection>& connections) {
    net::connection connection= myAcceptor.acceptConnection();
    std::cout << "Added connection: " << connection.getConnectionSocket() << std::endl;
    pollfd connectionPollFd = pollfd();
    connectionPollFd.events = POLLIN | POLLHUP;
    connectionPollFd.fd = connection.getConnectionSocket();
    fds.push_back(connectionPollFd);
    connections.push_back(connection);
}

void handleClient(std::vector<pollfd>& fds, std::vector<net::connection>& connections, int connectionIndex) {
    net::connection connection = connections[connectionIndex];
    net::RecvData incoming = connection.connectionReceive();
    if (incoming.closed) {
        std::cout << "A connection closed!" << std::endl;
        fds.erase(fds.begin()+connectionIndex+1);
        connections.erase(connections.begin()+connectionIndex);
    } else {
        for (int i=0;i<connections.size();i++) {
            if (i != connectionIndex) {
                std::cout << "Received data, sending to all connections..." << std::endl;
                connections[i].connectionSend(incoming.msg);
            }
        }
    }
}

void handleEvents(std::vector<pollfd>& fds, net::acceptor& myAcceptor, std::vector<net::connection>& connections) {
    for (int i=0; i<fds.size();i++) {
        pollfd cur = fds.at(i);
        std::cout << "Investigating: " << cur.fd << std::endl;
        std::cout << "Its revents is: " << cur.revents << std::endl;
        if (cur.revents & (POLLIN | POLLHUP)) {
            if (cur.fd == myAcceptor.getAcceptorSocket()) {
                std::cout << "An event happened with the acceptor." << std::endl;
                addConnection(fds, myAcceptor, connections);
            } else {
                std::cout << "An event happened with a client." << std::endl;
                handleClient(fds, connections, i-1);
            }
        } else {
            std::cout << "Nothing happened with this socket." << std::endl;
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
            std::cout << "Handling " << numEvents
            << " events" << std::endl;
            handleEvents(fds,myAcceptor, connections);
        }
    }
    return 0;
}