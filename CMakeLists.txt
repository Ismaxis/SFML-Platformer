cmake_minimum_required (VERSION 3.8)
project(Client VERSION 0.1.0)

add_compile_definitions(SFML_STATIC)

add_subdirectory(Client)
add_subdirectory(ServerLinux)
