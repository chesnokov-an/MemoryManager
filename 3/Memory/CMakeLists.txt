# cmake_minimum_required(VERSION 3.16)
# project(Memory)

# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g")

# add_library(Memory INTERFACE)

# target_include_directories(Memory INTERFACE include)
# ---------------
# cmake_minimum_required(VERSION 3.16)
# project(Memory)

# set(CMAKE_CXX_STANDARD 23)

# add_library(Memory STATIC   source/ArrayDescriptor.cpp
#                             source/Error.cpp
#                             source/MemoryElement.cpp
#                             source/Program.cpp
#                             source/ReferenceDescriptor.cpp
#                             source/SharedSegmentDescriptor.cpp
#                             source/VariableDescriptor.cpp)

# target_include_directories(Memory PUBLIC include)
# ------------------


cmake_minimum_required(VERSION 3.16)

project(Memory)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 🔹 Собираем все .cpp из source/
file(GLOB MEMORY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

# 🔹 Создаем статическую библиотеку Memory
add_library(Memory STATIC ${MEMORY_SOURCES})

# 🔹 Подключаем include/ как публичную директорию
target_include_directories(Memory PUBLIC include)

# (Опционально) включить более строгие предупреждения
target_compile_options(Memory PRIVATE
    -Wall -Wextra -Wpedantic
)
