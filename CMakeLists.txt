cmake_minimum_required(VERSION 3.5)
project(ray-tracer)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O3 -pthread")

include_directories(externals/concurrentqueue)

set(SOURCE_FILES src/main.cpp)
add_executable(ray-tracer ${SOURCE_FILES})