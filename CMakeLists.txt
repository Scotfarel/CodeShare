cmake_minimum_required(VERSION 3.11)

project(CodeShare)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror=pedantic")
set(CMAKE_C_STANDARD 99)
set(LIB_SOURCE_FILES
        project/src/RoomScheduler.cpp
        project/src/ChatRoom.cpp
        project/src/MongoConnector.cpp project/src/RoomTextBuilder.cpp)

include_directories(project/headers)

enable_testing()

add_executable(CodeShare project/src/main.cpp
        project/src/ChatRoom.cpp project/headers/ChatRoom.h
        project/src/RoomScheduler.cpp project/headers/RoomScheduler.h
        project/src/MongoConnector.cpp project/headers/MongoConnector.h project/src/RoomTextBuilder.cpp project/headers/RoomTextBuilder.h project/headers/TextBuilder.h)

add_library(project_lib STATIC ${LIB_SOURCE_FILES})

add_subdirectory(project/tests)
