cmake_minimum_required(VERSION 3.17)
project(documentAlignmentWithHomography)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

SET (OpenCV_STATIC ON)

file(COPY form.jpg scanned-form.jpg DESTINATION ${CMAKE_BINARY_DIR})

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(documentAlignmentWithHomography main.cpp)

TARGET_LINK_LIBRARIES(documentAlignmentWithHomography ${OpenCV_LIBS} )