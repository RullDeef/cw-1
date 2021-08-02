cmake_minimum_required(VERSION 3.19)
project(Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

include_directories(../Core/include)
include_directories(include)

add_executable(Tests
        main.cpp)

target_link_libraries(Tests Core)
