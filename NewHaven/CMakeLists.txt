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
include_directories(src)

add_executable(TurnSequenceTest test/TurnSequence.cpp src/Player.cpp src/GBMap.cpp src/VGMap.cpp src/Square.cpp src/Resources.cpp src/ResourceScore.cpp src/ScoreCalculator.cpp)
target_link_libraries (TurnSequenceTest ${Boost_LIBRARIES})