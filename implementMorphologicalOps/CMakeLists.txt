cmake_minimum_required(VERSION 3.17)
project(implementMorphologicalOps)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

SET (OpenCV_STATIC ON)

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(implementMorphologicalOps main.cpp)

TARGET_LINK_LIBRARIES(implementMorphologicalOps ${OpenCV_LIBS} )