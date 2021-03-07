cmake_minimum_required(VERSION 2.8)
project( DisplayImage CXX)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( choose_region choose_region.cc )
target_link_libraries( choose_region ${OpenCV_LIBS} )

add_executable( roi roi.cc )
target_link_libraries( roi ${OpenCV_LIBS} )

add_executable(exp exp.cc )
target_link_libraries( exp ${OpenCV_LIBS} )

