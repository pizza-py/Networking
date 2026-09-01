//
// Created by David Sorinola on 04/08/2026.
//

#ifndef NETWORKING_PARSING_H
#define NETWORKING_PARSING_H

#include "request.h"
#include <vector>

namespace http {
    std::vector<string> split(string, string);

    HTTPRequest parseHTTP(string);
}

#endif //NETWORKING_PARSING_H