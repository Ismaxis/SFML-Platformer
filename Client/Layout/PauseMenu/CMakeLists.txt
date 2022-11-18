cmake_minimum_required (VERSION 3.8)
project(PauseMenu)

# set(h 
#     "PauseMenu.h"
# )
# set(cpp 
#     "PauseMenu.cpp"
# )
 
# add_library(PauseMenu STATIC ${h} ${cpp})

# target_include_directories(PauseMenu PRIVATE "D:/SFML-CMake/include") 
# target_link_directories(PauseMenu PUBLIC "D:/SFML-CMake/lib")
# target_link_libraries(PauseMenu "sfml-graphics-s" "sfml-window-s" "sfml-system-s" "opengl32" "winmm" "gdi32" "freetype")

set(h 
    "${CMAKE_CURRENT_SOURCE_DIR}/PauseMenu.h"
)
set(cpp 
    "${CMAKE_CURRENT_SOURCE_DIR}/PauseMenu.cpp"
)
 

target_sources(Client PRIVATE ${h} ${cpp})
target_include_directories(Client PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
