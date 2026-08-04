//
// Created by David Sorinola on 01/08/2026.
//

#ifndef NETWORKING_REQUEST_H
#define NETWORKING_REQUEST_H
#include <string>

namespace http {
    using string = std::string;
    using string_view = std::string_view;
    struct HTTPRequest {
    private:
        string method;
        string requestTarget;
        string protocol;
        string host;
        string userAgent;
        string accept;
        string connection;
        bool valid;

    public:
        HTTPRequest(string_view = "", string_view="", string_view ="", string_view ="", string_view ="", string_view="", string_view = "");

        HTTPRequest(int fail);

        string getMethod();
        void setMethod(string x);

        string getRequestTarget();
        void setRequestTarget(string x);

        string getProtocol();
        void setProtocol(string x);

        string getHost();
        void setHost(string x);

        string getUserAgent();
        void setUserAgent(string x);

        string getAccept();
        void setAccept(string x);

        string getConnection();
        void setConnection(string x);

        bool getValid();
    };
}


#endif //NETWORKING_REQUEST_H