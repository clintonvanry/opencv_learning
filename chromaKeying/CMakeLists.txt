cmake_minimum_required(VERSION 3.17)
project(chromaKeying)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

SET (OpenCV_STATIC ON)

file(COPY greenscreen-asteroid.mp4 background.jpg astroid.png DESTINATION ${CMAKE_BINARY_DIR})

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(chromaKeying submission.cpp)

TARGET_LINK_LIBRARIES(chromaKeying ${OpenCV_LIBS} )