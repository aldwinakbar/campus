cmake_minimum_required(VERSION 2.8)
project( squares )
find_package( OpenCV REQUIRED )
add_executable( squares square.cpp )
target_link_libraries( squares ${OpenCV_LIBS} )
add_executable( square-HL square-HL.cpp )
target_link_libraries( square-HL ${OpenCV_LIBS} )
add_executable( square-HLBasic square-HLBasic.cpp )
target_link_libraries( square-HLBasic ${OpenCV_LIBS} )
add_executable( circle circle_detection.cpp )
target_link_libraries( circle ${OpenCV_LIBS} )
