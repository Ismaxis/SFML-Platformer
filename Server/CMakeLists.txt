cmake_minimum_required (VERSION 3.8)
project (Server)

add_executable (Server "Server.cpp" "NetworkLibrary.h" "Common.h")

target_link_libraries(Server PRIVATE "asio")
