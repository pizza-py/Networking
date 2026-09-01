//
// Created by David Sorinola on 12/08/2026.
//

#ifndef NETWORKING_RESPONSE_H
#define NETWORKING_RESPONSE_H

#include <string>


namespace http {
    using namespace std;
    class response {
    private:
        string protocol;
        string statusCode;
        string reasonPhrase;
        string server;
        string content;

    public:
        response(string statusCode="200", string reasonPhrase="OK", string protocol="HTTP/1.1", string server="", string content="");

        string getProtocol();
        void setProtocol(string);

        string getStatusCode();
        void setStatusCode(string);

        string getReasonPhrase();
        void setReasonPhrase(string);

        string getServer();
        void setServer(string);

        string getContent();
        void setContent(string);

        string buildResponse();

        operator string();
    };


}


#endif //NETWORKING_RESPONSE_H