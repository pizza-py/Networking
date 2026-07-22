//
// Created by David Sorinola on 08/07/2026.
//

#ifndef NETWORKING_ACCEPTOR_H
#define NETWORKING_ACCEPTOR_H

#include <string>
#include "connection.h"
#include <poll.h>

namespace net {
    class acceptor {
    private:
        bool blocking;
        int acceptorSocket;

    public:
        acceptor(std::string_view port);

        net::connection acceptConnection();

        bool isBlocking();

        void setBlocking(bool);

        int getAcceptorSocket();

        ~acceptor();

    };
}
#endif //NETWORKING_ACCEPTOR_H