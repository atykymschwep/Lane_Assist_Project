cmake_minimum_required(VERSION 3.10)
project(LaneDetection)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(LaneDetection main.cpp LaneDetector.cpp)

target_link_libraries(LaneDetection ${OpenCV_LIBS})