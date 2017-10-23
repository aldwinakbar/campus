cmake_minimum_required(VERSION 2.8.9)
project(as0308)

find_package( OpenCV REQUIRED )
#Bring the headers, such as Student.h into the project
include_directories(include)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/main.cpp)

#However, the file(GLOB...) allows for wildcard additions:
#file(GLOB SOURCES "src/*.cpp")
set (CMAKE_CXX_STANDARD 14)
add_executable(CVInterface src/main.cpp src/ImageAIO.cpp src/ImageProcessing.cpp )
target_link_libraries( CVInterface ${OpenCV_LIBS} )
add_executable(ARVision src/ARVision.cpp src/SmoothData.cpp src/PerimeterData.cpp src/RegionData.cpp src/PixelListData.cpp)
target_link_libraries( ARVision ${OpenCV_LIBS} )
