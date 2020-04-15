cmake_minimum_required(VERSION 3.11)

project(CodeShare)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror=pedantic")
set(CMAKE_C_STANDARD 99)

include_directories(project/headers)

enable_testing()

add_executable(CodeShare project/src/main.cpp
        project/src/Client.cpp project/headers/Client.h project/src/ConnectionHandler.cpp project/headers/ConnectionHandler.h project/src/GUI.cpp project/headers/GUI.h project/src/ClientTextManager.cpp project/headers/ClientTextManager.h project/src/TextManager.cpp project/headers/TextManager.h project/src/TextDiff.cpp project/headers/TextDiff.h)

add_subdirectory(project/tests)
