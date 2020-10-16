cmake_minimum_required(VERSION 3.17)
project(assignment_panorama)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

SET (OpenCV_STATIC ON)

file(COPY scene_result.png DESTINATION ${CMAKE_BINARY_DIR})

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(assignment_panorama main.cpp)

TARGET_LINK_LIBRARIES(assignment_panorama ${OpenCV_LIBS} )