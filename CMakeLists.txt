cmake_minimum_required(VERSION 3.3)
project(WeatherPlusPlus)
# qt5 meta objects
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# source code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp WeatherUi.h ApiUri.h ApiCall.h)
add_executable(WeatherPlusPlus ${SOURCE_FILES})
# qt5
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Network)
target_link_libraries(WeatherPlusPlus Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Network)
