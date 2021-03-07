cmake_minimum_required(VERSION 2.8)
project( DisplayImage CXX)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( canny canny.cc )
target_link_libraries( canny ${OpenCV_LIBS} )

add_executable( sobel sobel.cc )
target_link_libraries( sobel ${OpenCV_LIBS} )

add_executable( Laplacian Laplacian.cc )
target_link_libraries( Laplacian ${OpenCV_LIBS} )

