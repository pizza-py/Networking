//
// Created by David Sorinola on 01/08/2026.
//

#include "../include/request.h"
#include <utility>

namespace http {

    HTTPRequest::HTTPRequest(string method, string requestTarget, string protocol, string host, string userAgent, string accept, string connection) : method(method), requestTarget(requestTarget), protocol(protocol), host(host), userAgent(userAgent), accept(accept), connection(connection), valid(true) {}

    HTTPRequest::HTTPRequest(int fail) : valid(false), failCode(fail) {}


    string HTTPRequest::getMethod() {return method;}

    void HTTPRequest::setMethod(string x) {method = std::move(x);}

    string HTTPRequest::getRequestTarget() {return method;}

    void HTTPRequest::setRequestTarget(string x) {method = std::move(x);}

    string HTTPRequest::getProtocol() {return method;}

    void HTTPRequest::setProtocol(string x) {method = std::move(x);}

    string HTTPRequest::getHost() {return host;}

    void HTTPRequest::setHost(string x) {host = std::move(x);}

    string HTTPRequest::getUserAgent() {return userAgent;}

    void HTTPRequest::setUserAgent(string x) {userAgent = std::move(x);}

    string HTTPRequest::getAccept() {return accept;}

    void HTTPRequest::setAccept(string x) {accept = std::move(x);}

    string HTTPRequest::getConnection() {return connection;}

    void HTTPRequest::setConnection(string x) {connection = std::move(x);}

    bool HTTPRequest::getValid() {return valid;}

    int HTTPRequest::getFailCode() {return failCode;}



}