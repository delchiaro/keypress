cmake_minimum_required(VERSION 3.3)
project(keypress)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("debug mode")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/debug")

else(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("release mode")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/release")

endif (CMAKE_BUILD_TYPE STREQUAL "Debug")



file(GLOB MY_DLLS  "CMAKE_CURRENT_SOURCE_DIR}/dlls/*.dlls")
file(COPY ${MY_DLLS}  DESTINATION myDestination)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp aaa.h)
add_executable(keypress ${SOURCE_FILES})