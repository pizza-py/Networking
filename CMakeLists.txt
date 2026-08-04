cmake_minimum_required(VERSION 3.23)
project(Networking)

add_executable(serverTest
        examples/plainBlockingServer.cpp
        src/acceptor.cpp
        src/connection.cpp
)

add_executable(httpTest
        examples/httpMain.cpp
        http/request.cpp
        src/acceptor.cpp
        src/connection.cpp
        http/parsing.cpp
        include/parsing.h
)

add_executable(pollServerTest
        src/acceptor.cpp
        src/connection.cpp
        examples/pollServer.cpp
)

