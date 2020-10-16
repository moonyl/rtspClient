cmake_minimum_required(VERSION 3.17)
project(rtspClient)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED SSL Crypto)

find_library(liveMediaLib liveMedia REQUIRED)
find_library(groupsockLib groupsock REQUIRED)
find_library(UsageEnvironmentLib UsageEnvironment REQUIRED)
find_library(BasicUsageEnvironmentLib BasicUsageEnvironment REQUIRED)
message(STATUS "liveMedia=${liveMedia}")
find_path(liveMediaPath liveMedia.hh REQUIRED)
message(STATUS "liveMediaPath=${liveMediaPath}")

add_library(liveMedia STATIC IMPORTED)
set_target_properties(liveMedia PROPERTIES IMPORTED_LOCATION ${liveMediaLib})

add_library(groupsock STATIC IMPORTED)
set_target_properties(groupsock PROPERTIES IMPORTED_LOCATION ${groupsockLib})

add_library(UsageEnvironment STATIC IMPORTED)
set_target_properties(UsageEnvironment PROPERTIES IMPORTED_LOCATION ${UsageEnvironmentLib})

add_library(BasicUsageEnvironment STATIC IMPORTED)
set_target_properties(BasicUsageEnvironment PROPERTIES IMPORTED_LOCATION ${BasicUsageEnvironmentLib})

add_executable(rtspClient
        main.cpp
        testRTSPClient.cpp
        testRTSPClient.h)
target_link_libraries(rtspClient PRIVATE
        liveMedia BasicUsageEnvironment UsageEnvironment groupsock
        OpenSSL::SSL OpenSSL::Crypto ws2_32)
target_include_directories(rtspClient PRIVATE ${liveMediaPath})

add_subdirectory(test)

enable_testing()
include(CTest)
add_test(test test/rtspClient_test)