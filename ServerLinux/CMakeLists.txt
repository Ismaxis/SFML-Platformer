# CMakeList.txt : CMake project for ServerLinux, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ServerLinux")

# Add source to this project's executable.
add_executable (ServerLinux   "Server.cpp" "NetworkLibrary.h" "Common.h")

target_include_directories(ServerLinux PRIVATE "library" "D:/asio-1.24.0/include") 

# TODO: Add tests and install targets if needed.
