# cmake_minimum_required(VERSION 3.16)
# project(Memory)

# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g")

# add_library(Memory INTERFACE)

# target_include_directories(Memory INTERFACE include)

cmake_minimum_required(VERSION 3.16)
project(Memory)

set(CMAKE_CXX_STANDARD 23)

add_library(Memory STATIC   source/ArrayDescriptor.cpp
                            source/Error.cpp
                            source/MemoryElement.cpp
                            source/Program.cpp
                            source/ReferenceDescriptor.cpp
                            source/SharedSegmentDescriptor.cpp
                            source/VariableDescriptor.cpp)

target_include_directories(Memory PUBLIC include)