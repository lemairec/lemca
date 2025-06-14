cmake_minimum_required(VERSION 2.8)
project(lemca)

# The version number.
set (PROJECT_VERSION_MAJOR 25)
set (PROJECT_VERSION_MINOR 01)
set (PROJECT_VERSION_PATCH 05)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/environnement.hpp.in"
    "${PROJECT_BINARY_DIR}/environnement.hpp"
)
include_directories("${PROJECT_BINARY_DIR}")

if(APPLE)
    ADD_DEFINITIONS(-DAPPLE)
endif()

FIND_PACKAGE(Qt5Core)

set(CMAKE_AUTOMOC ON)

if(UNIX)
    ADD_DEFINITIONS(-std=c++0x -Wall)
    ADD_DEFINITIONS(-DUNIX)
    ADD_DEFINITIONS(-O3)
    #ADD_DEFINITIONS(-g -Wall)
endif()

find_package(Boost REQUIRED COMPONENTS system)
include_directories( ${Boost_INCLUDE_DIR}   )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

FILE(GLOB_RECURSE src_hpp src/*.hpp)
FILE(GLOB_RECURSE src_cpp src/*.cpp)
FILE(GLOB_RECURSE src_sh src/*.sh)

set(sources ${src_hpp} ${src_cpp} ${src_sh} ${PROJECT_BINARY_DIR}/environnement.hpp src/environnement.hpp.in README.md)

FIND_PACKAGE(Qt5Core)
add_executable(lemca ${sources})
qt5_use_modules(lemca Widgets SerialPort Network Core)

target_link_libraries(lemca ${Boost_LIBRARIES})

###
# grouping files for visual studio or xcode
###

SET(dirlist "")
FOREACH(file_path ${sources})
    GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
    IF(dir_path STREQUAL "")
    ELSE()
        STRING(REPLACE "${PROJECT_SOURCE_DIR}/" "" dir_path2 ${dir_path})
        SET(dir_list ${dir_list} ${dir_path2})
    ENDIF()
ENDFOREACH()
LIST(REMOVE_DUPLICATES dir_list)

foreach(next_ITEM ${dir_list})
    file(GLOB   source_ExecutionProvider_source ${next_ITEM}/*)
    STRING(REPLACE "/" "\\\\" source_group_path ${next_ITEM})
    source_group(${source_group_path} FILES ${source_ExecutionProvider_source})
endforeach(next_ITEM ${MY_SOURCES})
