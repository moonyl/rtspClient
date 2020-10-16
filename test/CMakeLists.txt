cmake_minimum_required(VERSION 3.17)
project(rtspClient_test)

add_executable(rtspClient_test test_main.cpp)
target_include_directories(rtspClient_test PRIVATE ../)