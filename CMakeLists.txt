cmake_minimum_required(VERSION 3.3)
project(WeatherPlusPlus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp ApiCall.h ApiCall.cpp)
add_executable(WeatherPlusPlus ${SOURCE_FILES})

find_package(cppnetlib 0.11.0 REQUIRED)
include_directories(${CPPNETLIB_INCLUDE_DIRS})
target_link_libraries(WeatherPlusPlus ${CPPNETLIB_LIBRARIES})
