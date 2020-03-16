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
add_executable(VGMap test/VGMapDriver.cpp src/VGMap.cpp src/Resources.cpp)
add_executable(GameBoardMapTest test/GBMapDriver.cpp src/GBMap.cpp src/Resources.cpp src/Square.cpp)
add_executable(MapLoaderTest test/MapLoaderDriver.cpp src/VGMapLoader.cpp src/VGMap.cpp src/GBMapLoader.cpp src/GBMap.cpp src/Square.cpp Exceptions/InvalidConfigurationException.cpp Exceptions/BoardConfigurationNotLoaded.cpp src/Resources.cpp)
add_executable(ResourcesTest test/ResourcesDriver.cpp src/Resources.cpp src/ResourceTracker.cpp)
add_executable(ScoreTest test/ScoreDriver.cpp src/GBMap.cpp src/Resources.cpp src/Square.cpp src/VGMap.cpp src/ScoreCalculator.cpp src/ResourceTracker.cpp)
add_executable(PlayerTest test/PlayerTest.cpp src/Player.cpp src/GBMap.cpp src/Square.cpp src/Resources.cpp src/VGMap.cpp src/ScoreCalculator.cpp src/ResourceTracker.cpp)
target_link_libraries (PlayerTest ${Boost_LIBRARIES})
target_link_libraries(MapLoaderTest   ${Boost_LIBRARIES})
target_link_libraries (VGMap ${Boost_LIBRARIES})
target_link_libraries (GameBoardMapTest ${Boost_LIBRARIES})
target_link_libraries (PlayerTest ${Boost_LIBRARIES})