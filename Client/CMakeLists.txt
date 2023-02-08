cmake_minimum_required (VERSION 3.8)
project(Client VERSION 0.1.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++17")

add_compile_definitions(SFML_STATIC)
set(CMAKE_PREFIX_PATH "~/vcpkg/packages/sfml_x64-linux/" "~/vcpkg/packages/asio_x64-linux/" ${CMAKE_PREFIX_PATH})


add_executable(Client
"${CMAKE_CURRENT_SOURCE_DIR}/Client.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Layout/CMakeLists.txt"
)
add_subdirectory(Layout)

find_package(asio CONFIG REQUIRED)
target_link_libraries(Client PRIVATE asio::asio)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(Client PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

#target_include_directories(Client PRIVATE "D:/SFML-CMake/include")
#target_link_directories(Client PUBLIC "D:/SFML-CMake/lib")
#target_link_libraries(Client PRIVATE "sfml-graphics-s" "sfml-window-s" "sfml-system-s" "opengl32" "winmm" "gdi32" "freetype" "asio")
