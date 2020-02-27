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

add_executable(VGMap test/VGMapDriver.cpp src/VGMap.cpp)
add_executable(GameBoardMapTest test/GBMapDriver.cpp src/GBMap.cpp src/Resources.cpp src/Square.cpp)
add_executable(ResourcesTest test/ResourcesDriver.cpp src/Resources.cpp)
add_executable(CalculatorTest test/CalculatorDriver.cpp src/Resources.cpp src/GBMap.cpp src/Square.cpp src/Calculations.cpp)
add_executable(VGMapScore test/VGMapScoreComputation.cpp src/Resources.cpp src/VGMap.cpp src/ScoreCalculator.cpp)
target_link_libraries (VGMap ${Boost_LIBRARIES})
target_link_libraries (GameBoardMapTest ${Boost_LIBRARIES})
target_link_libraries (VGMapScore ${Boost_LIBRARIES})
target_link_libraries (CalculatorTest ${Boost_LIBRARIES})
