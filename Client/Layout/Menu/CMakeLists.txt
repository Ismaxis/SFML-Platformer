cmake_minimum_required (VERSION 3.8)
project(Menu)

set(h 
    "${CMAKE_CURRENT_SOURCE_DIR}/Menu.h"
)
set(cpp 
    "${CMAKE_CURRENT_SOURCE_DIR}/Menu.cpp"
)
 
# add_library(Menu STATIC ${h} ${cpp})
target_sources(Client PRIVATE ${h} ${cpp})
target_include_directories(Client PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# target_include_directories(Menu PRIVATE "D:/SFML-CMake/include") 
# target_link_directories(Menu PUBLIC "D:/SFML-CMake/lib")
# target_link_libraries(Menu "sfml-graphics-s" "sfml-window-s" "sfml-system-s" "opengl32" "winmm" "gdi32" "freetype")
