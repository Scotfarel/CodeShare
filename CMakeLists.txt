cmake_minimum_required(VERSION 3.11)

project(CodeShare)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -ggdb3")

if (APPLE)
    set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
	set(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")
endif()

include_directories(project/headers)

set(SOURCE_DIR project/src/)

set(LIB_SOURCE_FILES
    ${SOURCE_DIR}Acceptor.cpp
    ${SOURCE_DIR}Server.cpp
    ${SOURCE_DIR}Connection.cpp
    ${SOURCE_DIR}ConnectionManager.cpp
    ${SOURCE_DIR}RequestHandler.cpp
)

add_library(project_lib STATIC ${LIB_SOURCE_FILES})

enable_testing()

add_executable(CodeShare ${SOURCE_DIR}main.cpp)

target_link_libraries(CodeShare project_lib)

add_subdirectory(project/tests)
