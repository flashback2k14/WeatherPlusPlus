cmake_minimum_required(VERSION 3.3)
project(WeatherAPI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CPPNETLIB_INCLUDE_DIRS "lib/cpp-netlib-0.11.2-final/")
set(SOURCE_FILES main.cpp ApiCall.h ApiCall.cpp)

add_executable(WeatherAPI ${SOURCE_FILES})

set ( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ~/cpp-netlib-build )
find_package ( cppnetlib 0.11.0 REQUIRED )
include_directories ( ${CPPNETLIB_INCLUDE_DIRS} )
target_link_libraries (WeatherAPI ${CPPNETLIB_LIBRARIES} )


