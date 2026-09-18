//
// Created by David Sorinola on 01/09/2026.
//

#include <gtest/gtest.h>
#include "../include/parsing.h"


//-----------------SPLITTING TESTS------------------------------//
TEST(SplitTests, HelloWorld) {
    auto myStrings = http::split("Hello World!", " ");
    std::vector<std::string> correctAnswer = {"Hello","World!"};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, HelloWorldEmptyDelimiter) {
    auto myStrings = http::split("Hello World!", "");
    std::vector<std::string> correctAnswer = {"Hello World!"};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, EmptyString) {
    auto myStrings = http::split("", ",");
    std::vector<std::string> correctAnswer = {""};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, EmptyStringEmptyDelimiter) {
    auto myStrings = http::split("", "");
    std::vector<std::string> correctAnswer = {""};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, MultipleCharDelimiter) {
    auto myStrings = http::split("abcdefg", "cd");
    std::vector<std::string> correctAnswer = {"ab","efg"};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, ConsecutiveDelimiters) {
    auto myStrings = http::split("Hello  World!", " ");
    std::vector<std::string> correctAnswer = {"Hello","","World!"};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, GreedySplit) {
    auto myStrings = http::split("ababab", "bab");
    std::vector<std::string> correctAnswer = {"a","ab"};
    ASSERT_EQ(myStrings, correctAnswer);
}

TEST(SplitTests, GreedySplit2) {
    auto myStrings = http::split("ababababababababcabababab", "bab");
    std::vector<std::string> correctAnswer = {"a","a","a","a","ca","a",""};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, StartsWithDelimiter) {
    auto myStrings = http::split(",He,llo", ",");
    std::vector<std::string> correctAnswer = {"", "He","llo"};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, EndsWithDelimiter) {
    auto myStrings = http::split("abcdefg,", ",");
    std::vector<std::string> correctAnswer = {"abcdefg",""};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, StartsAndEndsWithDelimiter) {
    auto myStrings = http::split(",abcdefg,", ",");
    std::vector<std::string> correctAnswer = {"","abcdefg",""};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, BigDelimiter) {
    auto myStrings = http::split("abcdefg", "abcdef");
    std::vector<std::string> correctAnswer = {"","g"};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, DelimiterIsSameAsString) {
    auto myStrings = http::split("Hello World!", "Hello World!");
    std::vector<std::string> correctAnswer = {"",""};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, DelimiterNotInString) {
    auto myStrings = http::split("Hello World!", "Bababooey");
    std::vector<std::string> correctAnswer = {"Hello World!"};
    ASSERT_EQ(myStrings,correctAnswer);
}

TEST(SplitTests, DelimiterIsCRLF) {
    auto myStrings = http::split("Hello\r\nWorld!", "\r\n");
    std::vector<std::string> correctAnswer = {"Hello","World!"};
    ASSERT_EQ(myStrings, correctAnswer);
}
//------------------------------Parse HTTP Tests-------------------//

TEST(HTTPParsingTests, HTTPGetRequest) {
    std::string myRequest = "GET / HTTP/1.1\r\n"
    "Host: example.com\r\n"
    "User-Agent: somethingsomething\r\n"
    "Accept: */*\r\n"
    "Connection: keep-alive";
    auto res = http::parseHTTP(myRequest);

    ASSERT_EQ(res.getMethod(), "GET");
    ASSERT_EQ(res.getRequestTarget(), "/");
    ASSERT_EQ(res.getProtocol(), "HTTP/1.1");
    ASSERT_EQ(res.getHost(), "example.com");
    ASSERT_EQ(res.getUserAgent(), "somethingsomething");
    ASSERT_EQ(res.getAccept(), "*/*");
    ASSERT_EQ(res.getConnection(), "keep-aliv");
    ASSERT_TRUE(res.getValid());
    ASSERT_EQ(res.getFailCode(), 0);
}