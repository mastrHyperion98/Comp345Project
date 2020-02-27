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
add_executable(MapLoaderTest test/MapLoaderDriver.cpp src/GBMapLoader.cpp src/GBMap.cpp src/Square.cpp Exceptions/InvalidConfigurationException.cpp Exceptions/BoardConfigurationNotLoaded.cpp)
add_executable(ResourcesTest test/ResourcesDriver.cpp src/Resources.cpp)
target_link_libraries(MapLoaderTest   ${Boost_LIBRARIES})
target_link_libraries (VGMap ${Boost_LIBRARIES})
target_link_libraries (GameBoardMapTest ${Boost_LIBRARIES})

