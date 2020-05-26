cmake_minimum_required(VERSION 3.13)
project(TextEditor)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR "YES")
set(CMAKE_AUTOMOC YES)
set(CMAKE_AUTOUIC YES)
set(CMAKE_AUTORCC YES)

set(SOURCES main.cpp
        src/File.cpp
        headers/File.h
        MyQTextEdit.h
        MyQTextEdit.cpp
        src/crdt.cpp
        headers/crdt.h
        editorwindow.cpp
        editorwindow.h
        editorwindow.ui
        src/jsonUtility.cpp
        headers/jsonUtility.h

        src/message.cpp
        headers/message.h
        myClient.cpp
        myClient.h
        src/symbol.cpp
        headers/symbol.h
        headers/json.hpp
        )

find_package(Boost 1.67.0 REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5 COMPONENTS Core WebSockets REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

list(APPEND LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::PrintSupport
        )

list(REMOVE_DUPLICATES LIBRARIES)

add_executable(Client ${SOURCES} ${Boost_INCLUDE_DIRS})
find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(Client ${Boost_LIBRARIES})
target_link_libraries(Client ${LIBRARIES} ${Boost_LIBRARIES})

