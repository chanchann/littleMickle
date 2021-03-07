cmake_minimum_required(VERSION 2.8)
project( DisplayImage CXX)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( houghline houghline.cc )
target_link_libraries( houghline ${OpenCV_LIBS} )
