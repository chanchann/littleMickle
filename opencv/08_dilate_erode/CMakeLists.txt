cmake_minimum_required(VERSION 2.8)
project( DisplayImage CXX)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( dilate dilate.cc )
target_link_libraries( dilate ${OpenCV_LIBS} )

add_executable( erode erode.cc )
target_link_libraries( erode ${OpenCV_LIBS} )

add_executable( morphology morphology.cc )
target_link_libraries( morphology ${OpenCV_LIBS} )

