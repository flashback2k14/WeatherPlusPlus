cmake_minimum_required(VERSION 3.3)
project(WeatherPlusPlus)
# source code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp ApiCall.h ApiCall.cpp WeatherUi.cpp WeatherUi.h)
add_executable(WeatherPlusPlus ${SOURCE_FILES})
# cppnet - both
find_package(cppnetlib 0.11.0 REQUIRED)
include_directories(${CPPNETLIB_INCLUDE_DIRS})
target_link_libraries(WeatherPlusPlus ${CPPNETLIB_LIBRARIES})
# qt5 - flashback2k14
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)
target_link_libraries(WeatherPlusPlus Qt5::Core Qt5::Widgets Qt5::Gui)
# qt5 - hetec
