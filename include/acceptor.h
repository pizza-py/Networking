//
// Created by David Sorinola on 08/07/2026.
//

#ifndef NETWORKING_ACCEPTOR_H
#define NETWORKING_ACCEPTOR_H

#include <string>
#include "connection.h"

namespace net {
    class acceptor {

    public: int acceptorSocket;

    public:
        acceptor(std::string_view port);

        net::connection blockingAccept();

        ~acceptor();
    };
}
#endif //NETWORKING_ACCEPTOR_H