cmake_minimum_required(VERSION 3.5)
project(FrammentiDiSogno)

set(CMAKE_CXX_STANDARD 17)

# This finds SDL2 (which does usually ship a config for CMake):
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Now use pkg-config to find SDL2_image
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

add_executable(FrammentiDiSogno
    src/main.cpp
    src/Game.cpp
    src/ResourceManager.cpp
    src/TileMap.cpp
)

target_include_directories(FrammentiDiSogno PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${SDL2_IMAGE_INCLUDE_DIRS}    # from pkg-config
)

target_link_libraries(FrammentiDiSogno
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}       # from pkg-config
)
