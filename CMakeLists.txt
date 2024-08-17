cmake_minimum_required(VERSION 3.10)
project(LowLife)

# Find the OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Specify the path to your source file and the name of the executable
add_executable(LowLife main.cpp)

# Link OpenCV libraries
target_link_libraries(LowLife ${OpenCV_LIBS})