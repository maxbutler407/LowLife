cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")

project(LowLife)

set(OpenCV_DIR "C:/msys64/ucrt64/lib/cmake/opencv4")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(LowLife 
    LowLife.cpp
    Enemy.cpp
    Player.cpp
    Utility.cpp
)

target_link_libraries(LowLife ${OpenCV_LIBS})

# copies photo and audio folders to the bin (so their paths arent based on my unique path from C drive)
file(COPY LowLifePhotos DESTINATION ${CMAKE_BINARY_DIR})
file(COPY LowLifeMusic DESTINATION ${CMAKE_BINARY_DIR})