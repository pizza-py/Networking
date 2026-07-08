cmake_minimum_required(VERSION 3.23)
project(Networking)

add_executable(main)


target_sources(main
        PRIVATE
        src/main.cpp)

target_sources(serverTest
        PRIVATE
        src/server.cpp
        include/acceptor.cpp)