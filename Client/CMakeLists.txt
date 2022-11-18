cmake_minimum_required (VERSION 3.8)
project(Client VERSION 0.1.0)

add_compile_definitions(SFML_STATIC)

add_executable(Client 
"${CMAKE_CURRENT_SOURCE_DIR}/Client.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Layout/CMakeLists.txt"
)

add_subdirectory(Layout)

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE "D:/asio-1.24.0/include")
target_link_libraries(asio INTERFACE "gdi32" "wsock32" "ws2_32")

target_include_directories(Client PRIVATE "D:/SFML-CMake/include") 
target_link_directories(Client PUBLIC "D:/SFML-CMake/lib")
target_link_libraries(Client PRIVATE "sfml-graphics-s" "sfml-window-s" "sfml-system-s" "opengl32" "winmm" "gdi32" "freetype" "asio")
