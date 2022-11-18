cmake_minimum_required (VERSION 3.8)
project (ServerLinux)

add_executable (ServerLinux "Server.cpp" "NetworkLibrary.h" "Common.h")

target_link_libraries(ServerLinux PRIVATE "asio")
