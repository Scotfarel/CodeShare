cmake_minimum_required(VERSION 3.11)
project(text_editor)
add_executable( main
        src/RoomTextManager.cpp
        headers/RoomTextManager.h
        src/ClientTextManager.cpp
        src/TextManager.cpp
        src/Traits.cpp
        src/main.cpp)
include_directories(headers)