cmake_minimum_required (VERSION 3.8)
project(Level)

set(h 
    "${CMAKE_CURRENT_SOURCE_DIR}/Camera.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Level.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Map.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Player.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/PlayerControls.h"
)
set(cpp 
    "${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Level.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Map.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp"
)
 
target_sources(Client PRIVATE ${h} ${cpp})
target_include_directories(Client PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
# target_include_directories(Client PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# target_include_directories(Level PRIVATE "library" "D:/asio-1.24.0/include") 

# target_include_directories(Level PRIVATE "D:/SFML-CMake/include") 
# target_link_directories(Level PUBLIC "D:/SFML-CMake/lib")
# target_link_libraries(Level "sfml-graphics-s" "sfml-window-s" "sfml-system-s" "opengl32" "winmm" "gdi32" "freetype")


