cmake_minimum_required(VERSION 3.13)
project(TextShareServer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

include_directories(project/headers)

set(SOURCE_DIR project/src/)

set(LIB_SOURCE_FILES
    ${SOURCE_DIR}Server.cpp
    ${SOURCE_DIR}Connection.cpp
    ${SOURCE_DIR}RequestHandler.cpp
)

add_library(project_lib STATIC ${LIB_SOURCE_FILES})

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
add_executable(TextShareServer ${SOURCE_DIR}main.cpp)

find_package(Boost 1.72.0 COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
endif()

target_link_libraries(TextShareServer project_lib ${Boost_LIBRARIES})

add_subdirectory(project/tests)
