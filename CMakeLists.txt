cmake_minimum_required(VERSION 2.8)
project(WeatherPlusPlus)
# qt5 meta objects
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# source code
file(COPY icons/ DESTINATION icons)
file(COPY weather++.sh/ DESTINATION weather++.sh)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp ApiCall.h ApiUri.h WeatherParser.h WeatherData.h WeatherMapper.h WeatherPages.h)
add_executable(WeatherPlusPlus ${SOURCE_FILES})
# qt5
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Network)
target_link_libraries(WeatherPlusPlus Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Network)
