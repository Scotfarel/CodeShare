cmake_minimum_required(VERSION 3.11)

project(CodeShare)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -ggdb3")

include_directories(project/headers)

set(LIB_SOURCE_FILES
    project/src/Acceptor.cpp
)

add_library(project_lib STATIC ${LIB_SOURCE_FILES})

enable_testing()

add_executable(CodeShare project/src/main.cpp)

target_link_libraries(CodeShare project_lib)

add_subdirectory(project/tests)
