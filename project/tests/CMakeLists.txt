cmake_minimum_required(VERSION 3.11)

project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -ggdb3")

find_package(GTest REQUIRED)

include_directories("${GTEST_INCLUDE_DIRS}")

add_executable(Tests
        src/main.cpp
        src/test_interface.cpp
        ../src/ChatRoom.cpp
        ../src/RoomManager.cpp
        ../src/MongoConnector.cpp
        )

set_target_properties(Tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

target_link_libraries(Tests ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

add_test(
        NAME BaseTest
        COMMAND tests --gtest_filter=-*Extra*
)
