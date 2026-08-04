//
// Created by David Sorinola on 04/08/2026.
//

#include "../include/parsing.h"

namespace http {
    std::vector<string_view> split(string_view str, string_view delimiter) {
        if (delimiter.empty()) {
            return std::vector<string_view>();
        }
        auto res = std::vector<string_view>();
        size_t left = 0;
        size_t right = 0;

        while ((right != string_view::npos) && (right < str.size())) {
            right = str.find(delimiter, left);
            if (right != string_view::npos) {
                res.push_back(str.substr(left,right-left));
            }
            left = right + delimiter.size();
        }

        if (res.size() == 0) {
            return res;
        }

        res.push_back(str.substr(left));

        return res;
    }

    HTTPRequest parseHTTP(string_view thing) {
        std::vector<string_view> fields = split(thing, "\r\n");
        if (fields.empty()) {
            return HTTPRequest(-1);
        } else {
            auto res = HTTPRequest();
            std::vector<string_view> head = split(fields.front(), " ");
            if (head.size() != 3) {
                return HTTPRequest(-1);
            } else if (head.front().data() != "GET") {
                return HTTPRequest(-1);
            } else {
                res.setMethod(head[0].data());
                res.setRequestTarget(head[1].data());
                res.setProtocol(head[2].data());
            }
            fields.erase(fields.begin());

            for (string_view field : fields) {
                std::vector<string_view> temp = split(field, ": ");
                if (temp.size() != 2) {
                    return HTTPRequest(-1);
                }

                if (temp[0] == "Host") {
                    res.setHost(temp[1].data());
                } else if (temp[0] == "User-Agent") {
                    res.setUserAgent(temp[1].data());
                } else if (temp[0] == "Accept") {
                    res.setAccept(temp[1].data());
                } else if (temp[0] == "Connection") {
                    res.setConnection(temp[1].data());
                }
            }

            return res;
        }

    }

}