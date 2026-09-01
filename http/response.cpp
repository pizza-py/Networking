//
// Created by David Sorinola on 12/08/2026.
//

#include "../include/response.h"
#include <iostream>

namespace http {
    response::response(string statusCode, string reasonPhrase, string protocol, string server, string content): protocol(protocol), statusCode(statusCode), reasonPhrase(reasonPhrase), server(server), content(content) {}

    string response::getProtocol() {return protocol;}
    void response::setProtocol(string x) {protocol = x;}

    string response::getStatusCode() {return statusCode;}
    void response::setStatusCode(string x) {statusCode = x;}

    string response::getReasonPhrase() {return reasonPhrase;}
    void response::setReasonPhrase(string x) {reasonPhrase = x;}

    string response::getServer() {return server;}
    void response::setServer(string x) {server = x;}

    string response::getContent() {return content;}
    void response::setContent(string x) {content = x;}

    string response::buildResponse() {
        if (statusCode.empty() || protocol.empty() || reasonPhrase.empty()) return "";
        string res;
        res += protocol + " " + statusCode + " " + reasonPhrase + "\r\n";
        if (!server.empty()) res += "Server: "+ server + "\r\n";
        if (!content.empty()) res += "Content-Length: " + std::to_string(content.length()) ;res+="\r\n\r\n";

        res += content + "\r\n\r\n";
        return res;
    }

    response::operator string() {
        return this->buildResponse();
    }



}