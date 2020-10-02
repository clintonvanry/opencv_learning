cmake_minimum_required(VERSION 3.17)
project(blemishRemoval)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

SET (OpenCV_STATIC ON)

file(COPY blemish.png  DESTINATION ${CMAKE_BINARY_DIR})

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(blemishRemoval submission.cpp)

TARGET_LINK_LIBRARIES(blemishRemoval ${OpenCV_LIBS} )