cmake_minimum_required(VERSION 3.12)
project(renda)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(renda/base)
add_subdirectory(renda/net)
