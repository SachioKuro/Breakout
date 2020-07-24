cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
project(Breakout)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} Breakout)

add_executable(breakout
    Breakout/Ball.cpp
    Breakout/Block.cpp
    Breakout/Block_Ball.cpp
    Breakout/Controller.cpp
    Breakout/Game.cpp
    Breakout/GameObject.cpp
    Breakout/LevelLoader.cpp
    Breakout/Main.cpp
    Breakout/MovableGameObject.cpp
    Breakout/Paddle.cpp
    Breakout/Physics.cpp
    Breakout/Renderer.cpp)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(breakout ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

FILE(COPY Breakout/tiles_breakout.png DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY Breakout/01.level DESTINATION "${CMAKE_BINARY_DIR}")