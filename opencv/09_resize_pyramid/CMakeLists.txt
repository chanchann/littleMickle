cmake_minimum_required(VERSION 2.8)
project( DisplayImage CXX)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( resize resize.cc )
target_link_libraries( resize ${OpenCV_LIBS} )

add_executable( resize_ratio resize_ratio.cc )
target_link_libraries( resize_ratio ${OpenCV_LIBS} )

add_executable( pry pry.cc )
target_link_libraries( pry ${OpenCV_LIBS} )

