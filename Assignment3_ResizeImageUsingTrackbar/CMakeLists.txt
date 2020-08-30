cmake_minimum_required(VERSION 3.17)
project(Assignment3_ResizeImageUsingTrackbar)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

SET (OpenCV_STATIC ON)

file(COPY truth.png DESTINATION ${CMAKE_BINARY_DIR})

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(Assignment3_ResizeImageUsingTrackbar submission.cpp)

TARGET_LINK_LIBRARIES(Assignment3_ResizeImageUsingTrackbar ${OpenCV_LIBS} )