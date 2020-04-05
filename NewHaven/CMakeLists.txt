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


add_executable(Part1 test/Part1Driver.cpp src/Setting.cpp src/Resources.cpp src/VGMap.cpp src/Player.cpp src/GBMap.cpp src/GBMapLoader.cpp src/Square.cpp src/ResourceTracker.cpp src/ScoreCalculator.cpp src/VGMapLoader.cpp Exceptions/InvalidConfigurationException.cpp Exceptions/BoardConfigurationNotLoaded.cpp src/GameController.cpp Exceptions/UninitializedControllerException.cpp)
add_executable(Part2 test/Part2Driver.cpp src/GameController.cpp src/Setting.cpp src/Resources.cpp src/VGMap.cpp src/Player.cpp src/GBMap.cpp src/GBMapLoader.cpp src/Square.cpp src/ResourceTracker.cpp src/ScoreCalculator.cpp src/VGMapLoader.cpp Exceptions/InvalidConfigurationException.cpp Exceptions/BoardConfigurationNotLoaded.cpp src/GameController.cpp Exceptions/UninitializedControllerException.cpp)
target_link_libraries (Part1 ${Boost_LIBRARIES})
target_link_libraries (Part2 ${Boost_LIBRARIES})
