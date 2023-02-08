cmake_minimum_required (VERSION 3.8)
project (Server)

add_executable (Server "Server.cpp" "NetworkLibrary.h" "Common.h")

#set_property(TARGET Server PROPERTY CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++17")

find_package(asio CONFIG REQUIRED)
target_link_libraries(Server PRIVATE asio::asio)