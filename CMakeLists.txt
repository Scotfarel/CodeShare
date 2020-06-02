cmake_minimum_required(VERSION 3.13)
project(TextEditor)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR "YES")
set(CMAKE_AUTOMOC YES)
#set(CMAKE_AUTOUIC YES)
set(SOURCES main.cpp
        src/File.cpp
        headers/File.h
        headers/TextEditor.h
        src/TextEditor.cpp
        src/NoteBook.ui
        src/NoteBook.cpp
        headers/NoteBook.h
        src/jsonTypes.cpp
        headers/jsonTypes.h
        src/Message.cpp
        headers/Message.h
        src/ClientConnector.cpp
        headers/ClientConnector.h
        src/symbol.cpp
        headers/symbol.h
        json.hpp
        src/CRDT.cpp
        headers/CRDT.h
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

