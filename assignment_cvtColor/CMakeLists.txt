cmake_minimum_required(VERSION 3.17)
project(assignment_cvtColor)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

SET (OpenCV_STATIC ON)

file(COPY sample.jpg sample01.jpg  DESTINATION ${CMAKE_BINARY_DIR})

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(assignment_cvtColor main.cpp)

TARGET_LINK_LIBRARIES(assignment_cvtColor ${OpenCV_LIBS} )