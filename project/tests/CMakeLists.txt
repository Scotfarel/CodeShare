cmake_minimum_required(VERSION 3.11)

project(test)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -ggdb3")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(GTest REQUIRED)


include_directories("${GTEST_INCLUDE_DIRS}")


function(_gmock_append_debugs _endvar _library)
    if(${_library} AND ${_library}_DEBUG)
        set(_output optimized ${${_library}} debug ${${_library}_DEBUG})
    else()
        set(_output ${${_library}})
    endif()
    set(${_endvar} ${_output} PARENT_SCOPE)
endfunction()

function(_gmock_find_library _name)
    find_library(${_name}
            NAMES ${ARGN}
            HINTS
            $ENV{GMOCK_ROOT}
            ${GMOCK_ROOT}
            PATH_SUFFIXES ${_gmock_libpath_suffixes}
            )
    mark_as_advanced(${_name})
endfunction()


if(NOT DEFINED GMOCK_MSVC_SEARCH)
    set(GMOCK_MSVC_SEARCH MD)
endif()

set(_gmock_libpath_suffixes lib)
if(MSVC)
    if(GMOCK_MSVC_SEARCH STREQUAL "MD")
        list(APPEND _gmock_libpath_suffixes
                msvc/gmock-md/Debug
                msvc/gmock-md/Release)
    elseif(GMOCK_MSVC_SEARCH STREQUAL "MT")
        list(APPEND _gmock_libpath_suffixes
                msvc/gmock/Debug
                msvc/gmock/Release)
    endif()
endif()

find_path(GMOCK_INCLUDE_DIR gmock/gmock.h
        HINTS
        $ENV{GMOCK_ROOT}/include
        ${GMOCK_ROOT}/include
        )
mark_as_advanced(GMOCK_INCLUDE_DIR)

if(MSVC AND GMOCK_MSVC_SEARCH STREQUAL "MD")
    # The provided /MD project files for Google Mock add -md suffixes to the
    # library names.
    _gmock_find_library(GMOCK_LIBRARY            gmock-md  gmock)
    _gmock_find_library(GMOCK_LIBRARY_DEBUG      gmock-mdd gmockd)
    _gmock_find_library(GMOCK_MAIN_LIBRARY       gmock_main-md  gmock_main)
    _gmock_find_library(GMOCK_MAIN_LIBRARY_DEBUG gmock_main-mdd gmock_maind)
else()
    _gmock_find_library(GMOCK_LIBRARY            gmock)
    _gmock_find_library(GMOCK_LIBRARY_DEBUG      gmockd)
    _gmock_find_library(GMOCK_MAIN_LIBRARY       gmock_main)
    _gmock_find_library(GMOCK_MAIN_LIBRARY_DEBUG gmock_maind)
endif()

FIND_PACKAGE_HANDLE_STANDARD_ARGS(GMock DEFAULT_MSG GMOCK_LIBRARY GMOCK_INCLUDE_DIR GMOCK_MAIN_LIBRARY)

if(GMOCK_FOUND)
    set(GMOCK_INCLUDE_DIRS ${GMOCK_INCLUDE_DIR})
    _gmock_append_debugs(GMOCK_LIBRARIES      GMOCK_LIBRARY)
    _gmock_append_debugs(GMOCK_MAIN_LIBRARIES GMOCK_MAIN_LIBRARY)
    set(GMOCK_BOTH_LIBRARIES ${GMOCK_LIBRARIES} ${GMOCK_MAIN_LIBRARIES})
endif()

add_executable(Tests
        src/main.cpp
        src/test_interface.cpp
      #  ../src/Client.cpp ../headers/Client.h ../src/ConnectionHandler.cpp ../headers/ConnectionHandler.h ../src/GUI.cpp ../headers/GUI.h ../src/ClientTextManager.cpp ../headers/ClientTextManager.h ../src/TextManager.cpp ../headers/TextManager.h ../src/TextDiff.cpp ../headers/TextDiff.h)
        )
set_target_properties(Tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

target_link_libraries(Tests ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES} project_lib)


add_test(
        NAME BaseTest
        COMMAND tests --gtest_filter=-*Extra*
)
