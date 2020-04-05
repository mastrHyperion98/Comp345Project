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

add_executable(VGMap src/VGMap.cpp src/Resources.cpp)
add_executable(GameBoardMapTest src/GBMap.cpp src/Resources.cpp src/Square.cpp)
add_executable(MapLoaderTest src/VGMapLoader.cpp src/VGMap.cpp src/GBMapLoader.cpp src/GBMap.cpp src/Square.cpp Exceptions/InvalidConfigurationException.cpp Exceptions/BoardConfigurationNotLoaded.cpp src/Resources.cpp)
add_executable(ResourcesTest test/ResourcesDriver.cpp src/Resources.cpp src/ResourceTracker.cpp)
add_executable(ScoreTest src/GBMap.cpp src/Resources.cpp src/Square.cpp src/VGMap.cpp src/ScoreCalculator.cpp src/ResourceTracker.cpp)
add_executable(PlayerTest test/PlayerTest.cpp src/Player.cpp  src/Resources.cpp src/VGMap.cpp src/ScoreCalculator.cpp src/ResourceTracker.cpp)
add_executable(Part-3_5-Test test/Part-3_5-Test.cpp src/Part-3_5.cpp src/Player.cpp src/Resources.cpp src/VGMap.cpp src/ScoreCalculator.cpp src/ResourceTracker.cpp src/GBMap.cpp src/Square.cpp)
add_executable(Part1 test/Part1Driver.cpp src/Setting.cpp src/Resources.cpp src/VGMap.cpp src/Player.cpp src/GBMap.cpp src/GBMapLoader.cpp src/Square.cpp src/ResourceTracker.cpp src/ScoreCalculator.cpp src/VGMapLoader.cpp Exceptions/InvalidConfigurationException.cpp Exceptions/BoardConfigurationNotLoaded.cpp src/GameController.cpp Exceptions/UninitializedControllerException.cpp)
add_executable(Part-3_6-Test test/Part-3_6-Test.cpp src/Part-3_6.cpp src/Player.cpp src/GBMap.cpp src/Square.cpp src/Resources.cpp src/ScoreCalculator.cpp src/ResourceTracker.cpp src/VGMap.cpp)
add_executable(TurnSequenceTest test/TurnSequence.cpp src/Player.cpp src/GBMap.cpp src/VGMap.cpp src/Square.cpp src/ResourceTracker.cpp src/ScoreCalculator.cpp src/Resources.cpp)
add_executable(Part-3_4-Test test/Part-3_4-Test.cpp src/Player.cpp src/GBMap.cpp src/Square.cpp src/Resources.cpp src/ScoreCalculator.cpp src/ResourceTracker.cpp src/VGMap.cpp)
add_executable(Part2 test/Part2Driver.cpp src/GameController.cpp src/Setting.cpp src/Resources.cpp src/VGMap.cpp src/Player.cpp src/GBMap.cpp src/GBMapLoader.cpp src/Square.cpp src/ResourceTracker.cpp src/ScoreCalculator.cpp src/VGMapLoader.cpp Exceptions/InvalidConfigurationException.cpp Exceptions/BoardConfigurationNotLoaded.cpp src/GameController.cpp Exceptions/UninitializedControllerException.cpp)
target_link_libraries (PlayerTest ${Boost_LIBRARIES})
target_link_libraries(MapLoaderTest   ${Boost_LIBRARIES})
target_link_libraries (VGMap ${Boost_LIBRARIES})
target_link_libraries (GameBoardMapTest ${Boost_LIBRARIES})
target_link_libraries (PlayerTest ${Boost_LIBRARIES})