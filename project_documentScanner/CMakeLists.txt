cmake_minimum_required(VERSION 3.17)
project(project_documentScanner)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

SET (OpenCV_STATIC ON)

file(COPY scanned-form.jpg DESTINATION ${CMAKE_BINARY_DIR})

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(project_documentScanner submission.cpp)

TARGET_LINK_LIBRARIES(project_documentScanner ${OpenCV_LIBS} )