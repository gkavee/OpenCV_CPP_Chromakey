cmake_minimum_required(VERSION 3.27)
project(chromakey)

set(CMAKE_CXX_STANDARD 17)
set(ENV{OPENCV_DIR} "C:\\tools\\opencv\\build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(chromakey main.cpp
        processImageRGB.cpp
        processImageHSV.cpp
        processImageRGB.h
        processImageHSV.h
        processVideo.cpp
        processVideo.h
        addMask.cpp
        addMask.h)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

target_link_libraries(chromakey ${OpenCV_LIBS})