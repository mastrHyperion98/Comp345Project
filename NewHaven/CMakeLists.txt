cmake_minimum_required(VERSION 3.15)
project(NewHaven)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
if(WIN32)
    #Execute Windows only command
    endif(WIN32)
if(UNIX)
    #Execute Unix only command
    endif(UNIX)

add_executable(NewHaven main.cpp)
add_executable(ResourcesTest test/ResourcesDriver.cpp src/Resources.cpp)

target_link_libraries (NewHaven ${Boost_LIBRARIES})
