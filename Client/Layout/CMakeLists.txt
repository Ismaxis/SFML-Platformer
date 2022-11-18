cmake_minimum_required (VERSION 3.8)
project(Layout)
 

set(h 
    "${CMAKE_CURRENT_SOURCE_DIR}/Button.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Inputs.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Layout.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/updateCodes.h"
)
set(cpp 
    "${CMAKE_CURRENT_SOURCE_DIR}/Button.cpp"
)

# add_library(Layout STATIC ${h} ${cpp})
target_sources(Client PRIVATE ${h} ${cpp}
    "${CMAKE_CURRENT_SOURCE_DIR}/Level/CMakeLists.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/Menu/CMakeLists.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/PauseMenu/CMakeLists.txt"
)
target_include_directories(Client PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(Level)
add_subdirectory(Menu)
add_subdirectory(PauseMenu)
# target_include_directories(Layout PRIVATE "D:/SFML-CMake/include") 
# target_link_directories(Layout PUBLIC "D:/SFML-CMake/lib")
# target_link_libraries(Layout "sfml-graphics-s" "sfml-window-s" "sfml-system-s" "opengl32" "winmm" "gdi32" "freetype")

# target_include_directories(MyLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
# target_compile_definitions(MyLib PUBLIC -DSOME_VAL=42)