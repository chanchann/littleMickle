cmake_minimum_required(VERSION 2.8)
project( DisplayImage CXX)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( test1 main.cc )
target_link_libraries( test1 ${OpenCV_LIBS} )

add_executable( at at.cc )
target_link_libraries( at ${OpenCV_LIBS} )

add_executable( iter iter.cc )
target_link_libraries( iter ${OpenCV_LIBS} )