cmake_minimum_required(VERSION 3.23)
project(Networking)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip
)
FetchContent_MakeAvailable(googletest)

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
        http/response.cpp
        include/response.h
)

add_executable(pollServerTest
        src/acceptor.cpp
        src/connection.cpp
        examples/pollServer.cpp
)

add_executable(tests
        tests/httpParsingTests.cpp
        http/parsing.cpp
        http/request.cpp
        http/response.cpp
)
target_link_libraries(tests
        PRIVATE
        GTest::gtest_main)