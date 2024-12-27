cmake_minimum_required(VERSION 3.5)
project(FrammentiDiSogno)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(FrammentiDiSogno
    src/main.cpp
    src/Game.cpp
)

target_include_directories(FrammentiDiSogno PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(FrammentiDiSogno
    ${SDL2_LIBRARIES}
)
