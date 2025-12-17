cmake_minimum_required(VERSION 3.16)

project(Memory)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g")

file(GLOB MEMORY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

add_library(Memory STATIC ${MEMORY_SOURCES})
target_include_directories(Memory PUBLIC include)

target_compile_options(Memory PRIVATE --coverage)
target_link_options(Memory PRIVATE --coverage)