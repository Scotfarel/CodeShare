cmake_minimum_required(VERSION 3.11)

project(CodeShare)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror=pedantic")
set(CMAKE_C_STANDARD 99)
set(LIB_SOURCE_FILES
        project/src/RoomManager.cpp
        project/src/ChatRoom.cpp
        project/src/MongoConnector.cpp project/src/RoomTextManager.cpp)

include_directories(project/headers)

enable_testing()

add_executable(CodeShare project/src/main.cpp
        project/src/ChatRoom.cpp project/headers/ChatRoom.h
        project/src/RoomManager.cpp project/headers/RoomManager.h
        project/src/MongoConnector.cpp project/headers/MongoConnector.h project/src/RoomTextManager.cpp project/headers/RoomTextManager.h project/headers/TextManger.h)

add_library(project_lib STATIC ${LIB_SOURCE_FILES})

add_subdirectory(project/tests)
