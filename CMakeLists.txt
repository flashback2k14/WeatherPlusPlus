cmake_minimum_required(VERSION 3.3)
project(WeatherAPI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CPPNETLIB_INCLUDE_DIRS "lib/cpp-netlib-0.11.2-final/")
set(SOURCE_FILES main.cpp)

include_directories ( ${CPPNETLIB_INCLUDE_DIRS} )

add_executable(WeatherAPI ${SOURCE_FILES})