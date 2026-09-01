//
// Created by David Sorinola on 04/08/2026.
//

#include "../include/parsing.h"
#include <iostream>

namespace http {
    std::vector<string> split(string str, string delimiter) {
        if (delimiter.empty()) {
            return std::vector<string>();
        }
        auto res = std::vector<string>();
        size_t left = 0;
        size_t right = 0;
        while ((right != string::npos) && (right < str.size())) {
            right = str.find(delimiter, left);
            if (right != string::npos) {
                res.push_back(str.substr(left,right-left));
                left = right + delimiter.size();
            }
        }

        if (res.size() == 0) {
            return res;
        }

        res.push_back(str.substr(left));

        return res;
    }

    HTTPRequest parseHTTP(string thing) {
        std::vector<string> fields = split(thing, "\r\n");
        if (fields.empty()) {
            return HTTPRequest(-1);
        } else {
            std::cerr << "Fields: " << std::endl;
            for (auto thingp : fields) {
                std::cerr << thingp << std::endl;
            }

            auto res = HTTPRequest();
            std::vector<string> head = split(fields.front(), " ");
            if (head.size() != 3) {
                return HTTPRequest(-2);
            } else if (head.front() != "GET") {
                std::cerr << "Things in header" << std::endl;
                for (auto i : head) {
                    std::cerr << i << std::endl;
                }
                return HTTPRequest(-3);
            } else {
                res.setMethod(head[0].data());
                res.setRequestTarget(head[1].data());
                res.setProtocol(head[2].data());
            }
            fields.erase(fields.begin());

            for (auto field : fields) {
                std::vector<string> temp = split(field, ": ");
                if (temp.size() != 2) {
                    return HTTPRequest(-4);
                }

                if (temp[0] == "Host") {
                    res.setHost(temp[1]);
                } else if (temp[0] == "User-Agent") {
                    res.setUserAgent(temp[1]);
                } else if (temp[0] == "Accept") {
                    res.setAccept(temp[1]);
                } else if (temp[0] == "Connection") {
                    res.setConnection(temp[1]);
                }
            }

            return res;
        }

    }

}