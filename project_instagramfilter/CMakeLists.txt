cmake_minimum_required(VERSION 3.17)
project(project_instagramfilter)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

SET (OpenCV_STATIC ON)

file(COPY trump.jpg expectedOutput.JPG  DESTINATION ${CMAKE_BINARY_DIR})

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(project_instagramfilter main.cpp)

TARGET_LINK_LIBRARIES(project_instagramfilter ${OpenCV_LIBS} )