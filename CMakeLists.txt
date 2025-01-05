cmake_minimum_required(VERSION 3.5)
project(FrammentiDiSogno)

set(CMAKE_CXX_STANDARD 17)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find SDL2_image
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

# Find SDL2_ttf
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

# Add the executable
add_executable(FrammentiDiSogno
    src/main.cpp
    src/Game.cpp
    src/ResourceManager.cpp
    src/TileMap.cpp
    src/Entity.cpp
    src/Player.cpp
    src/CollisionManager.cpp
    src/Dialogue.cpp
)

# Include directories
target_include_directories(FrammentiDiSogno PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${SDL2_IMAGE_INCLUDE_DIRS}    # SDL2_image include directories
    ${SDL2_TTF_INCLUDE_DIRS}      # SDL2_ttf include directories
)

# Link libraries
target_link_libraries(FrammentiDiSogno
    ${SDL2_LIBRARIES}             # SDL2 libraries
    ${SDL2_IMAGE_LIBRARIES}       # SDL2_image libraries
    ${SDL2_TTF_LIBRARIES}         # SDL2_ttf libraries
)
